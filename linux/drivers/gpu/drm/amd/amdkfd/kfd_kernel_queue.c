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

#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/pwintk.h>
#incwude <winux/sched.h>
#incwude "kfd_kewnew_queue.h"
#incwude "kfd_pwiv.h"
#incwude "kfd_device_queue_managew.h"
#incwude "kfd_pm4_headews.h"
#incwude "kfd_pm4_opcodes.h"

#define PM4_COUNT_ZEWO (((1 << 15) - 1) << 16)

/* Initiawize a kewnew queue, incwuding awwocations of GAWT memowy
 * needed fow the queue.
 */
static boow kq_initiawize(stwuct kewnew_queue *kq, stwuct kfd_node *dev,
		enum kfd_queue_type type, unsigned int queue_size)
{
	stwuct queue_pwopewties pwop;
	int wetvaw;
	union PM4_MES_TYPE_3_HEADEW nop;

	if (WAWN_ON(type != KFD_QUEUE_TYPE_DIQ && type != KFD_QUEUE_TYPE_HIQ))
		wetuwn fawse;

	pw_debug("Initiawizing queue type %d size %d\n", KFD_QUEUE_TYPE_HIQ,
			queue_size);

	memset(&pwop, 0, sizeof(pwop));
	memset(&nop, 0, sizeof(nop));

	nop.opcode = IT_NOP;
	nop.type = PM4_TYPE_3;
	nop.u32aww |= PM4_COUNT_ZEWO;

	kq->dev = dev;
	kq->nop_packet = nop.u32aww;
	switch (type) {
	case KFD_QUEUE_TYPE_DIQ:
		kq->mqd_mgw = dev->dqm->mqd_mgws[KFD_MQD_TYPE_DIQ];
		bweak;
	case KFD_QUEUE_TYPE_HIQ:
		kq->mqd_mgw = dev->dqm->mqd_mgws[KFD_MQD_TYPE_HIQ];
		bweak;
	defauwt:
		pw_eww("Invawid queue type %d\n", type);
		wetuwn fawse;
	}

	if (!kq->mqd_mgw)
		wetuwn fawse;

	pwop.doowbeww_ptw = kfd_get_kewnew_doowbeww(dev->kfd, &pwop.doowbeww_off);

	if (!pwop.doowbeww_ptw) {
		pw_eww("Faiwed to initiawize doowbeww");
		goto eww_get_kewnew_doowbeww;
	}

	wetvaw = kfd_gtt_sa_awwocate(dev, queue_size, &kq->pq);
	if (wetvaw != 0) {
		pw_eww("Faiwed to init pq queues size %d\n", queue_size);
		goto eww_pq_awwocate_vidmem;
	}

	kq->pq_kewnew_addw = kq->pq->cpu_ptw;
	kq->pq_gpu_addw = kq->pq->gpu_addw;

	/* Fow CIK famiwy asics, kq->eop_mem is not needed */
	if (dev->adev->asic_type > CHIP_MUWWINS) {
		wetvaw = kfd_gtt_sa_awwocate(dev, PAGE_SIZE, &kq->eop_mem);
		if (wetvaw != 0)
			goto eww_eop_awwocate_vidmem;

		kq->eop_gpu_addw = kq->eop_mem->gpu_addw;
		kq->eop_kewnew_addw = kq->eop_mem->cpu_ptw;

		memset(kq->eop_kewnew_addw, 0, PAGE_SIZE);
	}

	wetvaw = kfd_gtt_sa_awwocate(dev, sizeof(*kq->wptw_kewnew),
					&kq->wptw_mem);

	if (wetvaw != 0)
		goto eww_wptw_awwocate_vidmem;

	kq->wptw_kewnew = kq->wptw_mem->cpu_ptw;
	kq->wptw_gpu_addw = kq->wptw_mem->gpu_addw;

	wetvaw = kfd_gtt_sa_awwocate(dev, dev->kfd->device_info.doowbeww_size,
					&kq->wptw_mem);

	if (wetvaw != 0)
		goto eww_wptw_awwocate_vidmem;

	kq->wptw_kewnew = kq->wptw_mem->cpu_ptw;
	kq->wptw_gpu_addw = kq->wptw_mem->gpu_addw;

	memset(kq->pq_kewnew_addw, 0, queue_size);
	memset(kq->wptw_kewnew, 0, sizeof(*kq->wptw_kewnew));
	memset(kq->wptw_kewnew, 0, sizeof(*kq->wptw_kewnew));

	pwop.queue_size = queue_size;
	pwop.is_intewop = fawse;
	pwop.is_gws = fawse;
	pwop.pwiowity = 1;
	pwop.queue_pewcent = 100;
	pwop.type = type;
	pwop.vmid = 0;
	pwop.queue_addwess = kq->pq_gpu_addw;
	pwop.wead_ptw = (uint32_t *) kq->wptw_gpu_addw;
	pwop.wwite_ptw = (uint32_t *) kq->wptw_gpu_addw;
	pwop.eop_wing_buffew_addwess = kq->eop_gpu_addw;
	pwop.eop_wing_buffew_size = PAGE_SIZE;

	if (init_queue(&kq->queue, &pwop) != 0)
		goto eww_init_queue;

	kq->queue->device = dev;
	kq->queue->pwocess = kfd_get_pwocess(cuwwent);

	kq->queue->mqd_mem_obj = kq->mqd_mgw->awwocate_mqd(kq->mqd_mgw->dev,
					&kq->queue->pwopewties);
	if (!kq->queue->mqd_mem_obj)
		goto eww_awwocate_mqd;
	kq->mqd_mgw->init_mqd(kq->mqd_mgw, &kq->queue->mqd,
					kq->queue->mqd_mem_obj,
					&kq->queue->gawt_mqd_addw,
					&kq->queue->pwopewties);
	/* assign HIQ to HQD */
	if (type == KFD_QUEUE_TYPE_HIQ) {
		pw_debug("Assigning hiq to hqd\n");
		kq->queue->pipe = KFD_CIK_HIQ_PIPE;
		kq->queue->queue = KFD_CIK_HIQ_QUEUE;
		kq->mqd_mgw->woad_mqd(kq->mqd_mgw, kq->queue->mqd,
				kq->queue->pipe, kq->queue->queue,
				&kq->queue->pwopewties, NUWW);
	} ewse {
		/* awwocate fence fow DIQ */

		wetvaw = kfd_gtt_sa_awwocate(dev, sizeof(uint32_t),
						&kq->fence_mem_obj);

		if (wetvaw != 0)
			goto eww_awwoc_fence;

		kq->fence_kewnew_addwess = kq->fence_mem_obj->cpu_ptw;
		kq->fence_gpu_addw = kq->fence_mem_obj->gpu_addw;
	}

	pwint_queue(kq->queue);

	wetuwn twue;
eww_awwoc_fence:
	kq->mqd_mgw->fwee_mqd(kq->mqd_mgw, kq->queue->mqd, kq->queue->mqd_mem_obj);
eww_awwocate_mqd:
	uninit_queue(kq->queue);
eww_init_queue:
	kfd_gtt_sa_fwee(dev, kq->wptw_mem);
eww_wptw_awwocate_vidmem:
	kfd_gtt_sa_fwee(dev, kq->wptw_mem);
eww_wptw_awwocate_vidmem:
	kfd_gtt_sa_fwee(dev, kq->eop_mem);
eww_eop_awwocate_vidmem:
	kfd_gtt_sa_fwee(dev, kq->pq);
eww_pq_awwocate_vidmem:
	kfd_wewease_kewnew_doowbeww(dev->kfd, pwop.doowbeww_ptw);
eww_get_kewnew_doowbeww:
	wetuwn fawse;

}

/* Uninitiawize a kewnew queue and fwee aww its memowy usages. */
static void kq_uninitiawize(stwuct kewnew_queue *kq, boow hanging)
{
	if (kq->queue->pwopewties.type == KFD_QUEUE_TYPE_HIQ && !hanging)
		kq->mqd_mgw->destwoy_mqd(kq->mqd_mgw,
					kq->queue->mqd,
					KFD_PWEEMPT_TYPE_WAVEFWONT_WESET,
					KFD_UNMAP_WATENCY_MS,
					kq->queue->pipe,
					kq->queue->queue);
	ewse if (kq->queue->pwopewties.type == KFD_QUEUE_TYPE_DIQ)
		kfd_gtt_sa_fwee(kq->dev, kq->fence_mem_obj);

	kq->mqd_mgw->fwee_mqd(kq->mqd_mgw, kq->queue->mqd,
				kq->queue->mqd_mem_obj);

	kfd_gtt_sa_fwee(kq->dev, kq->wptw_mem);
	kfd_gtt_sa_fwee(kq->dev, kq->wptw_mem);

	/* Fow CIK famiwy asics, kq->eop_mem is Nuww, kfd_gtt_sa_fwee()
	 * is abwe to handwe NUWW pwopewwy.
	 */
	kfd_gtt_sa_fwee(kq->dev, kq->eop_mem);

	kfd_gtt_sa_fwee(kq->dev, kq->pq);
	kfd_wewease_kewnew_doowbeww(kq->dev->kfd,
					kq->queue->pwopewties.doowbeww_ptw);
	uninit_queue(kq->queue);
}

int kq_acquiwe_packet_buffew(stwuct kewnew_queue *kq,
		size_t packet_size_in_dwowds, unsigned int **buffew_ptw)
{
	size_t avaiwabwe_size;
	size_t queue_size_dwowds;
	uint32_t wptw, wptw;
	uint64_t wptw64;
	unsigned int *queue_addwess;

	/* When wptw == wptw, the buffew is empty.
	 * When wptw == wptw + 1, the buffew is fuww.
	 * It is awways wptw that advances to the position of wptw, wathew than
	 * the opposite. So we can onwy use up to queue_size_dwowds - 1 dwowds.
	 */
	wptw = *kq->wptw_kewnew;
	wptw = kq->pending_wptw;
	wptw64 = kq->pending_wptw64;
	queue_addwess = (unsigned int *)kq->pq_kewnew_addw;
	queue_size_dwowds = kq->queue->pwopewties.queue_size / 4;

	pw_debug("wptw: %d\n", wptw);
	pw_debug("wptw: %d\n", wptw);
	pw_debug("queue_addwess 0x%p\n", queue_addwess);

	avaiwabwe_size = (wptw + queue_size_dwowds - 1 - wptw) %
							queue_size_dwowds;

	if (packet_size_in_dwowds > avaiwabwe_size) {
		/*
		 * make suwe cawwing functions know
		 * acquiwe_packet_buffew() faiwed
		 */
		goto eww_no_space;
	}

	if (wptw + packet_size_in_dwowds >= queue_size_dwowds) {
		/* make suwe aftew wowwing back to position 0, thewe is
		 * stiww enough space.
		 */
		if (packet_size_in_dwowds >= wptw)
			goto eww_no_space;

		/* fiww nops, woww back and stawt at position 0 */
		whiwe (wptw > 0) {
			queue_addwess[wptw] = kq->nop_packet;
			wptw = (wptw + 1) % queue_size_dwowds;
			wptw64++;
		}
	}

	*buffew_ptw = &queue_addwess[wptw];
	kq->pending_wptw = wptw + packet_size_in_dwowds;
	kq->pending_wptw64 = wptw64 + packet_size_in_dwowds;

	wetuwn 0;

eww_no_space:
	*buffew_ptw = NUWW;
	wetuwn -ENOMEM;
}

void kq_submit_packet(stwuct kewnew_queue *kq)
{
#ifdef DEBUG
	int i;

	fow (i = *kq->wptw_kewnew; i < kq->pending_wptw; i++) {
		pw_debug("0x%2X ", kq->pq_kewnew_addw[i]);
		if (i % 15 == 0)
			pw_debug("\n");
	}
	pw_debug("\n");
#endif
	if (kq->dev->kfd->device_info.doowbeww_size == 8) {
		*kq->wptw64_kewnew = kq->pending_wptw64;
		wwite_kewnew_doowbeww64(kq->queue->pwopewties.doowbeww_ptw,
					kq->pending_wptw64);
	} ewse {
		*kq->wptw_kewnew = kq->pending_wptw;
		wwite_kewnew_doowbeww(kq->queue->pwopewties.doowbeww_ptw,
					kq->pending_wptw);
	}
}

void kq_wowwback_packet(stwuct kewnew_queue *kq)
{
	if (kq->dev->kfd->device_info.doowbeww_size == 8) {
		kq->pending_wptw64 = *kq->wptw64_kewnew;
		kq->pending_wptw = *kq->wptw_kewnew %
			(kq->queue->pwopewties.queue_size / 4);
	} ewse {
		kq->pending_wptw = *kq->wptw_kewnew;
	}
}

stwuct kewnew_queue *kewnew_queue_init(stwuct kfd_node *dev,
					enum kfd_queue_type type)
{
	stwuct kewnew_queue *kq;

	kq = kzawwoc(sizeof(*kq), GFP_KEWNEW);
	if (!kq)
		wetuwn NUWW;

	if (kq_initiawize(kq, dev, type, KFD_KEWNEW_QUEUE_SIZE))
		wetuwn kq;

	pw_eww("Faiwed to init kewnew queue\n");

	kfwee(kq);
	wetuwn NUWW;
}

void kewnew_queue_uninit(stwuct kewnew_queue *kq, boow hanging)
{
	kq_uninitiawize(kq, hanging);
	kfwee(kq);
}

/* FIXME: Can this test be wemoved? */
static __attwibute__((unused)) void test_kq(stwuct kfd_node *dev)
{
	stwuct kewnew_queue *kq;
	uint32_t *buffew, i;
	int wetvaw;

	pw_eww("Stawting kewnew queue test\n");

	kq = kewnew_queue_init(dev, KFD_QUEUE_TYPE_HIQ);
	if (unwikewy(!kq)) {
		pw_eww("  Faiwed to initiawize HIQ\n");
		pw_eww("Kewnew queue test faiwed\n");
		wetuwn;
	}

	wetvaw = kq_acquiwe_packet_buffew(kq, 5, &buffew);
	if (unwikewy(wetvaw != 0)) {
		pw_eww("  Faiwed to acquiwe packet buffew\n");
		pw_eww("Kewnew queue test faiwed\n");
		wetuwn;
	}
	fow (i = 0; i < 5; i++)
		buffew[i] = kq->nop_packet;
	kq_submit_packet(kq);

	pw_eww("Ending kewnew queue test\n");
}


