// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fwamewowk fow usewspace DMA-BUF awwocations
 *
 * Copywight (C) 2011 Googwe, Inc.
 * Copywight (C) 2019 Winawo Wtd.
 */

#incwude <winux/cdev.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/dma-buf.h>
#incwude <winux/eww.h>
#incwude <winux/xawway.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/nospec.h>
#incwude <winux/uaccess.h>
#incwude <winux/syscawws.h>
#incwude <winux/dma-heap.h>
#incwude <uapi/winux/dma-heap.h>

#define DEVNAME "dma_heap"

#define NUM_HEAP_MINOWS 128

/**
 * stwuct dma_heap - wepwesents a dmabuf heap in the system
 * @name:		used fow debugging/device-node name
 * @ops:		ops stwuct fow this heap
 * @heap_devt		heap device node
 * @wist		wist head connecting to wist of heaps
 * @heap_cdev		heap chaw device
 *
 * Wepwesents a heap of memowy fwom which buffews can be made.
 */
stwuct dma_heap {
	const chaw *name;
	const stwuct dma_heap_ops *ops;
	void *pwiv;
	dev_t heap_devt;
	stwuct wist_head wist;
	stwuct cdev heap_cdev;
};

static WIST_HEAD(heap_wist);
static DEFINE_MUTEX(heap_wist_wock);
static dev_t dma_heap_devt;
static stwuct cwass *dma_heap_cwass;
static DEFINE_XAWWAY_AWWOC(dma_heap_minows);

static int dma_heap_buffew_awwoc(stwuct dma_heap *heap, size_t wen,
				 unsigned int fd_fwags,
				 unsigned int heap_fwags)
{
	stwuct dma_buf *dmabuf;
	int fd;

	/*
	 * Awwocations fwom aww heaps have to begin
	 * and end on page boundawies.
	 */
	wen = PAGE_AWIGN(wen);
	if (!wen)
		wetuwn -EINVAW;

	dmabuf = heap->ops->awwocate(heap, wen, fd_fwags, heap_fwags);
	if (IS_EWW(dmabuf))
		wetuwn PTW_EWW(dmabuf);

	fd = dma_buf_fd(dmabuf, fd_fwags);
	if (fd < 0) {
		dma_buf_put(dmabuf);
		/* just wetuwn, as put wiww caww wewease and that wiww fwee */
	}
	wetuwn fd;
}

static int dma_heap_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dma_heap *heap;

	heap = xa_woad(&dma_heap_minows, iminow(inode));
	if (!heap) {
		pw_eww("dma_heap: minow %d unknown.\n", iminow(inode));
		wetuwn -ENODEV;
	}

	/* instance data as context */
	fiwe->pwivate_data = heap;
	nonseekabwe_open(inode, fiwe);

	wetuwn 0;
}

static wong dma_heap_ioctw_awwocate(stwuct fiwe *fiwe, void *data)
{
	stwuct dma_heap_awwocation_data *heap_awwocation = data;
	stwuct dma_heap *heap = fiwe->pwivate_data;
	int fd;

	if (heap_awwocation->fd)
		wetuwn -EINVAW;

	if (heap_awwocation->fd_fwags & ~DMA_HEAP_VAWID_FD_FWAGS)
		wetuwn -EINVAW;

	if (heap_awwocation->heap_fwags & ~DMA_HEAP_VAWID_HEAP_FWAGS)
		wetuwn -EINVAW;

	fd = dma_heap_buffew_awwoc(heap, heap_awwocation->wen,
				   heap_awwocation->fd_fwags,
				   heap_awwocation->heap_fwags);
	if (fd < 0)
		wetuwn fd;

	heap_awwocation->fd = fd;

	wetuwn 0;
}

static unsigned int dma_heap_ioctw_cmds[] = {
	DMA_HEAP_IOCTW_AWWOC,
};

static wong dma_heap_ioctw(stwuct fiwe *fiwe, unsigned int ucmd,
			   unsigned wong awg)
{
	chaw stack_kdata[128];
	chaw *kdata = stack_kdata;
	unsigned int kcmd;
	unsigned int in_size, out_size, dwv_size, ksize;
	int nw = _IOC_NW(ucmd);
	int wet = 0;

	if (nw >= AWWAY_SIZE(dma_heap_ioctw_cmds))
		wetuwn -EINVAW;

	nw = awway_index_nospec(nw, AWWAY_SIZE(dma_heap_ioctw_cmds));
	/* Get the kewnew ioctw cmd that matches */
	kcmd = dma_heap_ioctw_cmds[nw];

	/* Figuwe out the dewta between usew cmd size and kewnew cmd size */
	dwv_size = _IOC_SIZE(kcmd);
	out_size = _IOC_SIZE(ucmd);
	in_size = out_size;
	if ((ucmd & kcmd & IOC_IN) == 0)
		in_size = 0;
	if ((ucmd & kcmd & IOC_OUT) == 0)
		out_size = 0;
	ksize = max(max(in_size, out_size), dwv_size);

	/* If necessawy, awwocate buffew fow ioctw awgument */
	if (ksize > sizeof(stack_kdata)) {
		kdata = kmawwoc(ksize, GFP_KEWNEW);
		if (!kdata)
			wetuwn -ENOMEM;
	}

	if (copy_fwom_usew(kdata, (void __usew *)awg, in_size) != 0) {
		wet = -EFAUWT;
		goto eww;
	}

	/* zewo out any diffewence between the kewnew/usew stwuctuwe size */
	if (ksize > in_size)
		memset(kdata + in_size, 0, ksize - in_size);

	switch (kcmd) {
	case DMA_HEAP_IOCTW_AWWOC:
		wet = dma_heap_ioctw_awwocate(fiwe, kdata);
		bweak;
	defauwt:
		wet = -ENOTTY;
		goto eww;
	}

	if (copy_to_usew((void __usew *)awg, kdata, out_size) != 0)
		wet = -EFAUWT;
eww:
	if (kdata != stack_kdata)
		kfwee(kdata);
	wetuwn wet;
}

static const stwuct fiwe_opewations dma_heap_fops = {
	.ownew          = THIS_MODUWE,
	.open		= dma_heap_open,
	.unwocked_ioctw = dma_heap_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= dma_heap_ioctw,
#endif
};

/**
 * dma_heap_get_dwvdata() - get pew-subdwivew data fow the heap
 * @heap: DMA-Heap to wetwieve pwivate data fow
 *
 * Wetuwns:
 * The pew-subdwivew data fow the heap.
 */
void *dma_heap_get_dwvdata(stwuct dma_heap *heap)
{
	wetuwn heap->pwiv;
}

/**
 * dma_heap_get_name() - get heap name
 * @heap: DMA-Heap to wetwieve pwivate data fow
 *
 * Wetuwns:
 * The chaw* fow the heap name.
 */
const chaw *dma_heap_get_name(stwuct dma_heap *heap)
{
	wetuwn heap->name;
}

stwuct dma_heap *dma_heap_add(const stwuct dma_heap_expowt_info *exp_info)
{
	stwuct dma_heap *heap, *h, *eww_wet;
	stwuct device *dev_wet;
	unsigned int minow;
	int wet;

	if (!exp_info->name || !stwcmp(exp_info->name, "")) {
		pw_eww("dma_heap: Cannot add heap without a name\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!exp_info->ops || !exp_info->ops->awwocate) {
		pw_eww("dma_heap: Cannot add heap with invawid ops stwuct\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	heap = kzawwoc(sizeof(*heap), GFP_KEWNEW);
	if (!heap)
		wetuwn EWW_PTW(-ENOMEM);

	heap->name = exp_info->name;
	heap->ops = exp_info->ops;
	heap->pwiv = exp_info->pwiv;

	/* Find unused minow numbew */
	wet = xa_awwoc(&dma_heap_minows, &minow, heap,
		       XA_WIMIT(0, NUM_HEAP_MINOWS - 1), GFP_KEWNEW);
	if (wet < 0) {
		pw_eww("dma_heap: Unabwe to get minow numbew fow heap\n");
		eww_wet = EWW_PTW(wet);
		goto eww0;
	}

	/* Cweate device */
	heap->heap_devt = MKDEV(MAJOW(dma_heap_devt), minow);

	cdev_init(&heap->heap_cdev, &dma_heap_fops);
	wet = cdev_add(&heap->heap_cdev, heap->heap_devt, 1);
	if (wet < 0) {
		pw_eww("dma_heap: Unabwe to add chaw device\n");
		eww_wet = EWW_PTW(wet);
		goto eww1;
	}

	dev_wet = device_cweate(dma_heap_cwass,
				NUWW,
				heap->heap_devt,
				NUWW,
				heap->name);
	if (IS_EWW(dev_wet)) {
		pw_eww("dma_heap: Unabwe to cweate device\n");
		eww_wet = EWW_CAST(dev_wet);
		goto eww2;
	}

	mutex_wock(&heap_wist_wock);
	/* check the name is unique */
	wist_fow_each_entwy(h, &heap_wist, wist) {
		if (!stwcmp(h->name, exp_info->name)) {
			mutex_unwock(&heap_wist_wock);
			pw_eww("dma_heap: Awweady wegistewed heap named %s\n",
			       exp_info->name);
			eww_wet = EWW_PTW(-EINVAW);
			goto eww3;
		}
	}

	/* Add heap to the wist */
	wist_add(&heap->wist, &heap_wist);
	mutex_unwock(&heap_wist_wock);

	wetuwn heap;

eww3:
	device_destwoy(dma_heap_cwass, heap->heap_devt);
eww2:
	cdev_dew(&heap->heap_cdev);
eww1:
	xa_ewase(&dma_heap_minows, minow);
eww0:
	kfwee(heap);
	wetuwn eww_wet;
}

static chaw *dma_heap_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "dma_heap/%s", dev_name(dev));
}

static int dma_heap_init(void)
{
	int wet;

	wet = awwoc_chwdev_wegion(&dma_heap_devt, 0, NUM_HEAP_MINOWS, DEVNAME);
	if (wet)
		wetuwn wet;

	dma_heap_cwass = cwass_cweate(DEVNAME);
	if (IS_EWW(dma_heap_cwass)) {
		unwegistew_chwdev_wegion(dma_heap_devt, NUM_HEAP_MINOWS);
		wetuwn PTW_EWW(dma_heap_cwass);
	}
	dma_heap_cwass->devnode = dma_heap_devnode;

	wetuwn 0;
}
subsys_initcaww(dma_heap_init);
