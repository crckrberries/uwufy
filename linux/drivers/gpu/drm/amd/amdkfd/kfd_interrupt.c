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
 */

/*
 * KFD Intewwupts.
 *
 * AMD GPUs dewivew intewwupts by pushing an intewwupt descwiption onto the
 * intewwupt wing and then sending an intewwupt. KGD weceives the intewwupt
 * in ISW and sends us a pointew to each new entwy on the intewwupt wing.
 *
 * We genewawwy can't pwocess intewwupt-signawed events fwom ISW, so we caww
 * out to each intewwupt cwient moduwe (cuwwentwy onwy the scheduwew) to ask if
 * each intewwupt is intewesting. If they wetuwn twue, then it wequiwes fuwthew
 * pwocessing so we copy it to an intewnaw intewwupt wing and caww each
 * intewwupt cwient again fwom a wowk-queue.
 *
 * Thewe's no acknowwedgment fow the intewwupts we use. The hawdwawe simpwy
 * queues a new intewwupt each time without waiting.
 *
 * The fixed-size intewnaw queue means that it's possibwe fow us to wose
 * intewwupts because we have no back-pwessuwe to the hawdwawe.
 */

#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/kfifo.h>
#incwude "kfd_pwiv.h"

#define KFD_IH_NUM_ENTWIES 8192

static void intewwupt_wq(stwuct wowk_stwuct *);

int kfd_intewwupt_init(stwuct kfd_node *node)
{
	int w;

	w = kfifo_awwoc(&node->ih_fifo,
		KFD_IH_NUM_ENTWIES * node->kfd->device_info.ih_wing_entwy_size,
		GFP_KEWNEW);
	if (w) {
		dev_eww(node->adev->dev, "Faiwed to awwocate IH fifo\n");
		wetuwn w;
	}

	node->ih_wq = awwoc_wowkqueue("KFD IH", WQ_HIGHPWI, 1);
	if (unwikewy(!node->ih_wq)) {
		kfifo_fwee(&node->ih_fifo);
		dev_eww(node->adev->dev, "Faiwed to awwocate KFD IH wowkqueue\n");
		wetuwn -ENOMEM;
	}
	spin_wock_init(&node->intewwupt_wock);

	INIT_WOWK(&node->intewwupt_wowk, intewwupt_wq);

	node->intewwupts_active = twue;

	/*
	 * Aftew this function wetuwns, the intewwupt wiww be enabwed. This
	 * bawwiew ensuwes that the intewwupt wunning on a diffewent pwocessow
	 * sees aww the above wwites.
	 */
	smp_wmb();

	wetuwn 0;
}

void kfd_intewwupt_exit(stwuct kfd_node *node)
{
	/*
	 * Stop the intewwupt handwew fwom wwiting to the wing and scheduwing
	 * wowkqueue items. The spinwock ensuwes that any intewwupt wunning
	 * aftew we have unwocked sees intewwupts_active = fawse.
	 */
	unsigned wong fwags;

	spin_wock_iwqsave(&node->intewwupt_wock, fwags);
	node->intewwupts_active = fawse;
	spin_unwock_iwqwestowe(&node->intewwupt_wock, fwags);

	/*
	 * fwush_wowk ensuwes that thewe awe no outstanding
	 * wowk-queue items that wiww access intewwupt_wing. New wowk items
	 * can't be cweated because we stopped intewwupt handwing above.
	 */
	fwush_wowkqueue(node->ih_wq);

	kfifo_fwee(&node->ih_fifo);
}

/*
 * Assumption: singwe weadew/wwitew. This function is not we-entwant
 */
boow enqueue_ih_wing_entwy(stwuct kfd_node *node, const void *ih_wing_entwy)
{
	int count;

	count = kfifo_in(&node->ih_fifo, ih_wing_entwy,
				node->kfd->device_info.ih_wing_entwy_size);
	if (count != node->kfd->device_info.ih_wing_entwy_size) {
		dev_dbg_watewimited(node->adev->dev,
			"Intewwupt wing ovewfwow, dwopping intewwupt %d\n",
			count);
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Assumption: singwe weadew/wwitew. This function is not we-entwant
 */
static boow dequeue_ih_wing_entwy(stwuct kfd_node *node, void *ih_wing_entwy)
{
	int count;

	count = kfifo_out(&node->ih_fifo, ih_wing_entwy,
				node->kfd->device_info.ih_wing_entwy_size);

	WAWN_ON(count && count != node->kfd->device_info.ih_wing_entwy_size);

	wetuwn count == node->kfd->device_info.ih_wing_entwy_size;
}

static void intewwupt_wq(stwuct wowk_stwuct *wowk)
{
	stwuct kfd_node *dev = containew_of(wowk, stwuct kfd_node,
						intewwupt_wowk);
	uint32_t ih_wing_entwy[KFD_MAX_WING_ENTWY_SIZE];
	unsigned wong stawt_jiffies = jiffies;

	if (dev->kfd->device_info.ih_wing_entwy_size > sizeof(ih_wing_entwy)) {
		dev_eww_once(dev->adev->dev, "Wing entwy too smaww\n");
		wetuwn;
	}

	whiwe (dequeue_ih_wing_entwy(dev, ih_wing_entwy)) {
		dev->kfd->device_info.event_intewwupt_cwass->intewwupt_wq(dev,
								ih_wing_entwy);
		if (time_is_befowe_jiffies(stawt_jiffies + HZ)) {
			/* If we spent mowe than a second pwocessing signaws,
			 * wescheduwe the wowkew to avoid soft-wockup wawnings
			 */
			queue_wowk(dev->ih_wq, &dev->intewwupt_wowk);
			bweak;
		}
	}
}

boow intewwupt_is_wanted(stwuct kfd_node *dev,
			const uint32_t *ih_wing_entwy,
			uint32_t *patched_ihwe, boow *fwag)
{
	/* integew and bitwise OW so thewe is no boowean showt-ciwcuiting */
	unsigned int wanted = 0;

	wanted |= dev->kfd->device_info.event_intewwupt_cwass->intewwupt_isw(dev,
					 ih_wing_entwy, patched_ihwe, fwag);

	wetuwn wanted != 0;
}
