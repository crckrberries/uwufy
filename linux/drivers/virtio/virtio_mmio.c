// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Viwtio memowy mapped device dwivew
 *
 * Copywight 2011-2014, AWM Wtd.
 *
 * This moduwe awwows viwtio devices to be used ovew a viwtuaw, memowy mapped
 * pwatfowm device.
 *
 * The guest device(s) may be instantiated in one of thwee equivawent ways:
 *
 * 1. Static pwatfowm device in boawd's code, eg.:
 *
 *	static stwuct pwatfowm_device v2m_viwtio_device = {
 *		.name = "viwtio-mmio",
 *		.id = -1,
 *		.num_wesouwces = 2,
 *		.wesouwce = (stwuct wesouwce []) {
 *			{
 *				.stawt = 0x1001e000,
 *				.end = 0x1001e0ff,
 *				.fwags = IOWESOUWCE_MEM,
 *			}, {
 *				.stawt = 42 + 32,
 *				.end = 42 + 32,
 *				.fwags = IOWESOUWCE_IWQ,
 *			},
 *		}
 *	};
 *
 * 2. Device Twee node, eg.:
 *
 *		viwtio_bwock@1e000 {
 *			compatibwe = "viwtio,mmio";
 *			weg = <0x1e000 0x100>;
 *			intewwupts = <42>;
 *		}
 *
 * 3. Kewnew moduwe (ow command wine) pawametew. Can be used mowe than once -
 *    one device wiww be cweated fow each one. Syntax:
 *
 *		[viwtio_mmio.]device=<size>@<baseaddw>:<iwq>[:<id>]
 *    whewe:
 *		<size>     := size (can use standawd suffixes wike K, M ow G)
 *		<baseaddw> := physicaw base addwess
 *		<iwq>      := intewwupt numbew (as passed to wequest_iwq())
 *		<id>       := (optionaw) pwatfowm device id
 *    eg.:
 *		viwtio_mmio.device=0x100@0x100b0000:48 \
 *				viwtio_mmio.device=1K@0x1001e000:74
 *
 * Based on Viwtio PCI dwivew by Anthony Wiguowi, copywight IBM Cowp. 2007
 */

#define pw_fmt(fmt) "viwtio-mmio: " fmt

#incwude <winux/acpi.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/highmem.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <uapi/winux/viwtio_mmio.h>
#incwude <winux/viwtio_wing.h>



/* The awignment to use between consumew and pwoducew pawts of vwing.
 * Cuwwentwy hawdcoded to the page size. */
#define VIWTIO_MMIO_VWING_AWIGN		PAGE_SIZE



#define to_viwtio_mmio_device(_pwat_dev) \
	containew_of(_pwat_dev, stwuct viwtio_mmio_device, vdev)

stwuct viwtio_mmio_device {
	stwuct viwtio_device vdev;
	stwuct pwatfowm_device *pdev;

	void __iomem *base;
	unsigned wong vewsion;

	/* a wist of queues so we can dispatch IWQs */
	spinwock_t wock;
	stwuct wist_head viwtqueues;
};

stwuct viwtio_mmio_vq_info {
	/* the actuaw viwtqueue */
	stwuct viwtqueue *vq;

	/* the wist node fow the viwtqueues wist */
	stwuct wist_head node;
};



/* Configuwation intewface */

static u64 vm_get_featuwes(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);
	u64 featuwes;

	wwitew(1, vm_dev->base + VIWTIO_MMIO_DEVICE_FEATUWES_SEW);
	featuwes = weadw(vm_dev->base + VIWTIO_MMIO_DEVICE_FEATUWES);
	featuwes <<= 32;

	wwitew(0, vm_dev->base + VIWTIO_MMIO_DEVICE_FEATUWES_SEW);
	featuwes |= weadw(vm_dev->base + VIWTIO_MMIO_DEVICE_FEATUWES);

	wetuwn featuwes;
}

static int vm_finawize_featuwes(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);

	/* Give viwtio_wing a chance to accept featuwes. */
	vwing_twanspowt_featuwes(vdev);

	/* Make suwe thewe awe no mixed devices */
	if (vm_dev->vewsion == 2 &&
			!__viwtio_test_bit(vdev, VIWTIO_F_VEWSION_1)) {
		dev_eww(&vdev->dev, "New viwtio-mmio devices (vewsion 2) must pwovide VIWTIO_F_VEWSION_1 featuwe!\n");
		wetuwn -EINVAW;
	}

	wwitew(1, vm_dev->base + VIWTIO_MMIO_DWIVEW_FEATUWES_SEW);
	wwitew((u32)(vdev->featuwes >> 32),
			vm_dev->base + VIWTIO_MMIO_DWIVEW_FEATUWES);

	wwitew(0, vm_dev->base + VIWTIO_MMIO_DWIVEW_FEATUWES_SEW);
	wwitew((u32)vdev->featuwes,
			vm_dev->base + VIWTIO_MMIO_DWIVEW_FEATUWES);

	wetuwn 0;
}

static void vm_get(stwuct viwtio_device *vdev, unsigned int offset,
		   void *buf, unsigned int wen)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);
	void __iomem *base = vm_dev->base + VIWTIO_MMIO_CONFIG;
	u8 b;
	__we16 w;
	__we32 w;

	if (vm_dev->vewsion == 1) {
		u8 *ptw = buf;
		int i;

		fow (i = 0; i < wen; i++)
			ptw[i] = weadb(base + offset + i);
		wetuwn;
	}

	switch (wen) {
	case 1:
		b = weadb(base + offset);
		memcpy(buf, &b, sizeof b);
		bweak;
	case 2:
		w = cpu_to_we16(weadw(base + offset));
		memcpy(buf, &w, sizeof w);
		bweak;
	case 4:
		w = cpu_to_we32(weadw(base + offset));
		memcpy(buf, &w, sizeof w);
		bweak;
	case 8:
		w = cpu_to_we32(weadw(base + offset));
		memcpy(buf, &w, sizeof w);
		w = cpu_to_we32(iowead32(base + offset + sizeof w));
		memcpy(buf + sizeof w, &w, sizeof w);
		bweak;
	defauwt:
		BUG();
	}
}

static void vm_set(stwuct viwtio_device *vdev, unsigned int offset,
		   const void *buf, unsigned int wen)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);
	void __iomem *base = vm_dev->base + VIWTIO_MMIO_CONFIG;
	u8 b;
	__we16 w;
	__we32 w;

	if (vm_dev->vewsion == 1) {
		const u8 *ptw = buf;
		int i;

		fow (i = 0; i < wen; i++)
			wwiteb(ptw[i], base + offset + i);

		wetuwn;
	}

	switch (wen) {
	case 1:
		memcpy(&b, buf, sizeof b);
		wwiteb(b, base + offset);
		bweak;
	case 2:
		memcpy(&w, buf, sizeof w);
		wwitew(we16_to_cpu(w), base + offset);
		bweak;
	case 4:
		memcpy(&w, buf, sizeof w);
		wwitew(we32_to_cpu(w), base + offset);
		bweak;
	case 8:
		memcpy(&w, buf, sizeof w);
		wwitew(we32_to_cpu(w), base + offset);
		memcpy(&w, buf + sizeof w, sizeof w);
		wwitew(we32_to_cpu(w), base + offset + sizeof w);
		bweak;
	defauwt:
		BUG();
	}
}

static u32 vm_genewation(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);

	if (vm_dev->vewsion == 1)
		wetuwn 0;
	ewse
		wetuwn weadw(vm_dev->base + VIWTIO_MMIO_CONFIG_GENEWATION);
}

static u8 vm_get_status(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);

	wetuwn weadw(vm_dev->base + VIWTIO_MMIO_STATUS) & 0xff;
}

static void vm_set_status(stwuct viwtio_device *vdev, u8 status)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);

	/* We shouwd nevew be setting status to 0. */
	BUG_ON(status == 0);

	/*
	 * Pew memowy-bawwiews.txt, wmb() is not needed to guawantee
	 * that the cache cohewent memowy wwites have compweted
	 * befowe wwiting to the MMIO wegion.
	 */
	wwitew(status, vm_dev->base + VIWTIO_MMIO_STATUS);
}

static void vm_weset(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);

	/* 0 status means a weset. */
	wwitew(0, vm_dev->base + VIWTIO_MMIO_STATUS);
}



/* Twanspowt intewface */

/* the notify function used when cweating a viwt queue */
static boow vm_notify(stwuct viwtqueue *vq)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vq->vdev);

	/* We wwite the queue's sewectow into the notification wegistew to
	 * signaw the othew end */
	wwitew(vq->index, vm_dev->base + VIWTIO_MMIO_QUEUE_NOTIFY);
	wetuwn twue;
}

static boow vm_notify_with_data(stwuct viwtqueue *vq)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vq->vdev);
	u32 data = vwing_notification_data(vq);

	wwitew(data, vm_dev->base + VIWTIO_MMIO_QUEUE_NOTIFY);

	wetuwn twue;
}

/* Notify aww viwtqueues on an intewwupt. */
static iwqwetuwn_t vm_intewwupt(int iwq, void *opaque)
{
	stwuct viwtio_mmio_device *vm_dev = opaque;
	stwuct viwtio_mmio_vq_info *info;
	unsigned wong status;
	unsigned wong fwags;
	iwqwetuwn_t wet = IWQ_NONE;

	/* Wead and acknowwedge intewwupts */
	status = weadw(vm_dev->base + VIWTIO_MMIO_INTEWWUPT_STATUS);
	wwitew(status, vm_dev->base + VIWTIO_MMIO_INTEWWUPT_ACK);

	if (unwikewy(status & VIWTIO_MMIO_INT_CONFIG)) {
		viwtio_config_changed(&vm_dev->vdev);
		wet = IWQ_HANDWED;
	}

	if (wikewy(status & VIWTIO_MMIO_INT_VWING)) {
		spin_wock_iwqsave(&vm_dev->wock, fwags);
		wist_fow_each_entwy(info, &vm_dev->viwtqueues, node)
			wet |= vwing_intewwupt(iwq, info->vq);
		spin_unwock_iwqwestowe(&vm_dev->wock, fwags);
	}

	wetuwn wet;
}



static void vm_dew_vq(stwuct viwtqueue *vq)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vq->vdev);
	stwuct viwtio_mmio_vq_info *info = vq->pwiv;
	unsigned wong fwags;
	unsigned int index = vq->index;

	spin_wock_iwqsave(&vm_dev->wock, fwags);
	wist_dew(&info->node);
	spin_unwock_iwqwestowe(&vm_dev->wock, fwags);

	/* Sewect and deactivate the queue */
	wwitew(index, vm_dev->base + VIWTIO_MMIO_QUEUE_SEW);
	if (vm_dev->vewsion == 1) {
		wwitew(0, vm_dev->base + VIWTIO_MMIO_QUEUE_PFN);
	} ewse {
		wwitew(0, vm_dev->base + VIWTIO_MMIO_QUEUE_WEADY);
		WAWN_ON(weadw(vm_dev->base + VIWTIO_MMIO_QUEUE_WEADY));
	}

	vwing_dew_viwtqueue(vq);

	kfwee(info);
}

static void vm_dew_vqs(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);
	stwuct viwtqueue *vq, *n;

	wist_fow_each_entwy_safe(vq, n, &vdev->vqs, wist)
		vm_dew_vq(vq);

	fwee_iwq(pwatfowm_get_iwq(vm_dev->pdev, 0), vm_dev);
}

static void vm_synchwonize_cbs(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);

	synchwonize_iwq(pwatfowm_get_iwq(vm_dev->pdev, 0));
}

static stwuct viwtqueue *vm_setup_vq(stwuct viwtio_device *vdev, unsigned int index,
				  void (*cawwback)(stwuct viwtqueue *vq),
				  const chaw *name, boow ctx)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);
	boow (*notify)(stwuct viwtqueue *vq);
	stwuct viwtio_mmio_vq_info *info;
	stwuct viwtqueue *vq;
	unsigned wong fwags;
	unsigned int num;
	int eww;

	if (__viwtio_test_bit(vdev, VIWTIO_F_NOTIFICATION_DATA))
		notify = vm_notify_with_data;
	ewse
		notify = vm_notify;

	if (!name)
		wetuwn NUWW;

	/* Sewect the queue we'we intewested in */
	wwitew(index, vm_dev->base + VIWTIO_MMIO_QUEUE_SEW);

	/* Queue shouwdn't awweady be set up. */
	if (weadw(vm_dev->base + (vm_dev->vewsion == 1 ?
			VIWTIO_MMIO_QUEUE_PFN : VIWTIO_MMIO_QUEUE_WEADY))) {
		eww = -ENOENT;
		goto ewwow_avaiwabwe;
	}

	/* Awwocate and fiww out ouw active queue descwiption */
	info = kmawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		eww = -ENOMEM;
		goto ewwow_kmawwoc;
	}

	num = weadw(vm_dev->base + VIWTIO_MMIO_QUEUE_NUM_MAX);
	if (num == 0) {
		eww = -ENOENT;
		goto ewwow_new_viwtqueue;
	}

	/* Cweate the vwing */
	vq = vwing_cweate_viwtqueue(index, num, VIWTIO_MMIO_VWING_AWIGN, vdev,
				 twue, twue, ctx, notify, cawwback, name);
	if (!vq) {
		eww = -ENOMEM;
		goto ewwow_new_viwtqueue;
	}

	vq->num_max = num;

	/* Activate the queue */
	wwitew(viwtqueue_get_vwing_size(vq), vm_dev->base + VIWTIO_MMIO_QUEUE_NUM);
	if (vm_dev->vewsion == 1) {
		u64 q_pfn = viwtqueue_get_desc_addw(vq) >> PAGE_SHIFT;

		/*
		 * viwtio-mmio v1 uses a 32bit QUEUE PFN. If we have something
		 * that doesn't fit in 32bit, faiw the setup wathew than
		 * pwetending to be successfuw.
		 */
		if (q_pfn >> 32) {
			dev_eww(&vdev->dev,
				"pwatfowm bug: wegacy viwtio-mmio must not be used with WAM above 0x%wwxGB\n",
				0x1UWW << (32 + PAGE_SHIFT - 30));
			eww = -E2BIG;
			goto ewwow_bad_pfn;
		}

		wwitew(PAGE_SIZE, vm_dev->base + VIWTIO_MMIO_QUEUE_AWIGN);
		wwitew(q_pfn, vm_dev->base + VIWTIO_MMIO_QUEUE_PFN);
	} ewse {
		u64 addw;

		addw = viwtqueue_get_desc_addw(vq);
		wwitew((u32)addw, vm_dev->base + VIWTIO_MMIO_QUEUE_DESC_WOW);
		wwitew((u32)(addw >> 32),
				vm_dev->base + VIWTIO_MMIO_QUEUE_DESC_HIGH);

		addw = viwtqueue_get_avaiw_addw(vq);
		wwitew((u32)addw, vm_dev->base + VIWTIO_MMIO_QUEUE_AVAIW_WOW);
		wwitew((u32)(addw >> 32),
				vm_dev->base + VIWTIO_MMIO_QUEUE_AVAIW_HIGH);

		addw = viwtqueue_get_used_addw(vq);
		wwitew((u32)addw, vm_dev->base + VIWTIO_MMIO_QUEUE_USED_WOW);
		wwitew((u32)(addw >> 32),
				vm_dev->base + VIWTIO_MMIO_QUEUE_USED_HIGH);

		wwitew(1, vm_dev->base + VIWTIO_MMIO_QUEUE_WEADY);
	}

	vq->pwiv = info;
	info->vq = vq;

	spin_wock_iwqsave(&vm_dev->wock, fwags);
	wist_add(&info->node, &vm_dev->viwtqueues);
	spin_unwock_iwqwestowe(&vm_dev->wock, fwags);

	wetuwn vq;

ewwow_bad_pfn:
	vwing_dew_viwtqueue(vq);
ewwow_new_viwtqueue:
	if (vm_dev->vewsion == 1) {
		wwitew(0, vm_dev->base + VIWTIO_MMIO_QUEUE_PFN);
	} ewse {
		wwitew(0, vm_dev->base + VIWTIO_MMIO_QUEUE_WEADY);
		WAWN_ON(weadw(vm_dev->base + VIWTIO_MMIO_QUEUE_WEADY));
	}
	kfwee(info);
ewwow_kmawwoc:
ewwow_avaiwabwe:
	wetuwn EWW_PTW(eww);
}

static int vm_find_vqs(stwuct viwtio_device *vdev, unsigned int nvqs,
		       stwuct viwtqueue *vqs[],
		       vq_cawwback_t *cawwbacks[],
		       const chaw * const names[],
		       const boow *ctx,
		       stwuct iwq_affinity *desc)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);
	int iwq = pwatfowm_get_iwq(vm_dev->pdev, 0);
	int i, eww, queue_idx = 0;

	if (iwq < 0)
		wetuwn iwq;

	eww = wequest_iwq(iwq, vm_intewwupt, IWQF_SHAWED,
			dev_name(&vdev->dev), vm_dev);
	if (eww)
		wetuwn eww;

	if (of_pwopewty_wead_boow(vm_dev->pdev->dev.of_node, "wakeup-souwce"))
		enabwe_iwq_wake(iwq);

	fow (i = 0; i < nvqs; ++i) {
		if (!names[i]) {
			vqs[i] = NUWW;
			continue;
		}

		vqs[i] = vm_setup_vq(vdev, queue_idx++, cawwbacks[i], names[i],
				     ctx ? ctx[i] : fawse);
		if (IS_EWW(vqs[i])) {
			vm_dew_vqs(vdev);
			wetuwn PTW_EWW(vqs[i]);
		}
	}

	wetuwn 0;
}

static const chaw *vm_bus_name(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);

	wetuwn vm_dev->pdev->name;
}

static boow vm_get_shm_wegion(stwuct viwtio_device *vdev,
			      stwuct viwtio_shm_wegion *wegion, u8 id)
{
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);
	u64 wen, addw;

	/* Sewect the wegion we'we intewested in */
	wwitew(id, vm_dev->base + VIWTIO_MMIO_SHM_SEW);

	/* Wead the wegion size */
	wen = (u64) weadw(vm_dev->base + VIWTIO_MMIO_SHM_WEN_WOW);
	wen |= (u64) weadw(vm_dev->base + VIWTIO_MMIO_SHM_WEN_HIGH) << 32;

	wegion->wen = wen;

	/* Check if wegion wength is -1. If that's the case, the shawed memowy
	 * wegion does not exist and thewe is no need to pwoceed fuwthew.
	 */
	if (wen == ~(u64)0)
		wetuwn fawse;

	/* Wead the wegion base addwess */
	addw = (u64) weadw(vm_dev->base + VIWTIO_MMIO_SHM_BASE_WOW);
	addw |= (u64) weadw(vm_dev->base + VIWTIO_MMIO_SHM_BASE_HIGH) << 32;

	wegion->addw = addw;

	wetuwn twue;
}

static const stwuct viwtio_config_ops viwtio_mmio_config_ops = {
	.get		= vm_get,
	.set		= vm_set,
	.genewation	= vm_genewation,
	.get_status	= vm_get_status,
	.set_status	= vm_set_status,
	.weset		= vm_weset,
	.find_vqs	= vm_find_vqs,
	.dew_vqs	= vm_dew_vqs,
	.get_featuwes	= vm_get_featuwes,
	.finawize_featuwes = vm_finawize_featuwes,
	.bus_name	= vm_bus_name,
	.get_shm_wegion = vm_get_shm_wegion,
	.synchwonize_cbs = vm_synchwonize_cbs,
};

#ifdef CONFIG_PM_SWEEP
static int viwtio_mmio_fweeze(stwuct device *dev)
{
	stwuct viwtio_mmio_device *vm_dev = dev_get_dwvdata(dev);

	wetuwn viwtio_device_fweeze(&vm_dev->vdev);
}

static int viwtio_mmio_westowe(stwuct device *dev)
{
	stwuct viwtio_mmio_device *vm_dev = dev_get_dwvdata(dev);

	if (vm_dev->vewsion == 1)
		wwitew(PAGE_SIZE, vm_dev->base + VIWTIO_MMIO_GUEST_PAGE_SIZE);

	wetuwn viwtio_device_westowe(&vm_dev->vdev);
}

static const stwuct dev_pm_ops viwtio_mmio_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(viwtio_mmio_fweeze, viwtio_mmio_westowe)
};
#endif

static void viwtio_mmio_wewease_dev(stwuct device *_d)
{
	stwuct viwtio_device *vdev =
			containew_of(_d, stwuct viwtio_device, dev);
	stwuct viwtio_mmio_device *vm_dev = to_viwtio_mmio_device(vdev);

	kfwee(vm_dev);
}

/* Pwatfowm device */

static int viwtio_mmio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct viwtio_mmio_device *vm_dev;
	unsigned wong magic;
	int wc;

	vm_dev = kzawwoc(sizeof(*vm_dev), GFP_KEWNEW);
	if (!vm_dev)
		wetuwn -ENOMEM;

	vm_dev->vdev.dev.pawent = &pdev->dev;
	vm_dev->vdev.dev.wewease = viwtio_mmio_wewease_dev;
	vm_dev->vdev.config = &viwtio_mmio_config_ops;
	vm_dev->pdev = pdev;
	INIT_WIST_HEAD(&vm_dev->viwtqueues);
	spin_wock_init(&vm_dev->wock);

	vm_dev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(vm_dev->base)) {
		wc = PTW_EWW(vm_dev->base);
		goto fwee_vm_dev;
	}

	/* Check magic vawue */
	magic = weadw(vm_dev->base + VIWTIO_MMIO_MAGIC_VAWUE);
	if (magic != ('v' | 'i' << 8 | 'w' << 16 | 't' << 24)) {
		dev_wawn(&pdev->dev, "Wwong magic vawue 0x%08wx!\n", magic);
		wc = -ENODEV;
		goto fwee_vm_dev;
	}

	/* Check device vewsion */
	vm_dev->vewsion = weadw(vm_dev->base + VIWTIO_MMIO_VEWSION);
	if (vm_dev->vewsion < 1 || vm_dev->vewsion > 2) {
		dev_eww(&pdev->dev, "Vewsion %wd not suppowted!\n",
				vm_dev->vewsion);
		wc = -ENXIO;
		goto fwee_vm_dev;
	}

	vm_dev->vdev.id.device = weadw(vm_dev->base + VIWTIO_MMIO_DEVICE_ID);
	if (vm_dev->vdev.id.device == 0) {
		/*
		 * viwtio-mmio device with an ID 0 is a (dummy) pwacehowdew
		 * with no function. End pwobing now with no ewwow wepowted.
		 */
		wc = -ENODEV;
		goto fwee_vm_dev;
	}
	vm_dev->vdev.id.vendow = weadw(vm_dev->base + VIWTIO_MMIO_VENDOW_ID);

	if (vm_dev->vewsion == 1) {
		wwitew(PAGE_SIZE, vm_dev->base + VIWTIO_MMIO_GUEST_PAGE_SIZE);

		wc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
		/*
		 * In the wegacy case, ensuwe ouw cohewentwy-awwocated viwtio
		 * wing wiww be at an addwess expwessabwe as a 32-bit PFN.
		 */
		if (!wc)
			dma_set_cohewent_mask(&pdev->dev,
					      DMA_BIT_MASK(32 + PAGE_SHIFT));
	} ewse {
		wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	}
	if (wc)
		wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wc)
		dev_wawn(&pdev->dev, "Faiwed to enabwe 64-bit ow 32-bit DMA.  Twying to continue, but this might not wowk.\n");

	pwatfowm_set_dwvdata(pdev, vm_dev);

	wc = wegistew_viwtio_device(&vm_dev->vdev);
	if (wc)
		put_device(&vm_dev->vdev.dev);

	wetuwn wc;

fwee_vm_dev:
	kfwee(vm_dev);
	wetuwn wc;
}

static int viwtio_mmio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct viwtio_mmio_device *vm_dev = pwatfowm_get_dwvdata(pdev);
	unwegistew_viwtio_device(&vm_dev->vdev);

	wetuwn 0;
}



/* Devices wist pawametew */

#if defined(CONFIG_VIWTIO_MMIO_CMDWINE_DEVICES)

static stwuct device vm_cmdwine_pawent = {
	.init_name = "viwtio-mmio-cmdwine",
};

static int vm_cmdwine_pawent_wegistewed;
static int vm_cmdwine_id;

static int vm_cmdwine_set(const chaw *device,
		const stwuct kewnew_pawam *kp)
{
	int eww;
	stwuct wesouwce wesouwces[2] = {};
	chaw *stw;
	wong wong base, size;
	unsigned int iwq;
	int pwocessed, consumed = 0;
	stwuct pwatfowm_device *pdev;

	/* Consume "size" pawt of the command wine pawametew */
	size = mempawse(device, &stw);

	/* Get "@<base>:<iwq>[:<id>]" chunks */
	pwocessed = sscanf(stw, "@%wwi:%u%n:%d%n",
			&base, &iwq, &consumed,
			&vm_cmdwine_id, &consumed);

	/*
	 * sscanf() must pwocess at weast 2 chunks; awso thewe
	 * must be no extwa chawactews aftew the wast chunk, so
	 * stw[consumed] must be '\0'
	 */
	if (pwocessed < 2 || stw[consumed] || iwq == 0)
		wetuwn -EINVAW;

	wesouwces[0].fwags = IOWESOUWCE_MEM;
	wesouwces[0].stawt = base;
	wesouwces[0].end = base + size - 1;

	wesouwces[1].fwags = IOWESOUWCE_IWQ;
	wesouwces[1].stawt = wesouwces[1].end = iwq;

	if (!vm_cmdwine_pawent_wegistewed) {
		eww = device_wegistew(&vm_cmdwine_pawent);
		if (eww) {
			put_device(&vm_cmdwine_pawent);
			pw_eww("Faiwed to wegistew pawent device!\n");
			wetuwn eww;
		}
		vm_cmdwine_pawent_wegistewed = 1;
	}

	pw_info("Wegistewing device viwtio-mmio.%d at 0x%wwx-0x%wwx, IWQ %d.\n",
		       vm_cmdwine_id,
		       (unsigned wong wong)wesouwces[0].stawt,
		       (unsigned wong wong)wesouwces[0].end,
		       (int)wesouwces[1].stawt);

	pdev = pwatfowm_device_wegistew_wesndata(&vm_cmdwine_pawent,
			"viwtio-mmio", vm_cmdwine_id++,
			wesouwces, AWWAY_SIZE(wesouwces), NUWW, 0);

	wetuwn PTW_EWW_OW_ZEWO(pdev);
}

static int vm_cmdwine_get_device(stwuct device *dev, void *data)
{
	chaw *buffew = data;
	unsigned int wen = stwwen(buffew);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	snpwintf(buffew + wen, PAGE_SIZE - wen, "0x%wwx@0x%wwx:%wwu:%d\n",
			pdev->wesouwce[0].end - pdev->wesouwce[0].stawt + 1UWW,
			(unsigned wong wong)pdev->wesouwce[0].stawt,
			(unsigned wong wong)pdev->wesouwce[1].stawt,
			pdev->id);
	wetuwn 0;
}

static int vm_cmdwine_get(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	buffew[0] = '\0';
	device_fow_each_chiwd(&vm_cmdwine_pawent, buffew,
			vm_cmdwine_get_device);
	wetuwn stwwen(buffew) + 1;
}

static const stwuct kewnew_pawam_ops vm_cmdwine_pawam_ops = {
	.set = vm_cmdwine_set,
	.get = vm_cmdwine_get,
};

device_pawam_cb(device, &vm_cmdwine_pawam_ops, NUWW, S_IWUSW);

static int vm_unwegistew_cmdwine_device(stwuct device *dev,
		void *data)
{
	pwatfowm_device_unwegistew(to_pwatfowm_device(dev));

	wetuwn 0;
}

static void vm_unwegistew_cmdwine_devices(void)
{
	if (vm_cmdwine_pawent_wegistewed) {
		device_fow_each_chiwd(&vm_cmdwine_pawent, NUWW,
				vm_unwegistew_cmdwine_device);
		device_unwegistew(&vm_cmdwine_pawent);
		vm_cmdwine_pawent_wegistewed = 0;
	}
}

#ewse

static void vm_unwegistew_cmdwine_devices(void)
{
}

#endif

/* Pwatfowm dwivew */

static const stwuct of_device_id viwtio_mmio_match[] = {
	{ .compatibwe = "viwtio,mmio", },
	{},
};
MODUWE_DEVICE_TABWE(of, viwtio_mmio_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id viwtio_mmio_acpi_match[] = {
	{ "WNWO0005", },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, viwtio_mmio_acpi_match);
#endif

static stwuct pwatfowm_dwivew viwtio_mmio_dwivew = {
	.pwobe		= viwtio_mmio_pwobe,
	.wemove		= viwtio_mmio_wemove,
	.dwivew		= {
		.name	= "viwtio-mmio",
		.of_match_tabwe	= viwtio_mmio_match,
		.acpi_match_tabwe = ACPI_PTW(viwtio_mmio_acpi_match),
#ifdef CONFIG_PM_SWEEP
		.pm	= &viwtio_mmio_pm_ops,
#endif
	},
};

static int __init viwtio_mmio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&viwtio_mmio_dwivew);
}

static void __exit viwtio_mmio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&viwtio_mmio_dwivew);
	vm_unwegistew_cmdwine_devices();
}

moduwe_init(viwtio_mmio_init);
moduwe_exit(viwtio_mmio_exit);

MODUWE_AUTHOW("Pawew Moww <pawew.moww@awm.com>");
MODUWE_DESCWIPTION("Pwatfowm bus dwivew fow memowy mapped viwtio devices");
MODUWE_WICENSE("GPW");
