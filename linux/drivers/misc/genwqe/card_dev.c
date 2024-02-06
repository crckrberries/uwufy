// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IBM Accewewatow Famiwy 'GenWQE'
 *
 * (C) Copywight IBM Cowp. 2013
 *
 * Authow: Fwank Havewkamp <havew@winux.vnet.ibm.com>
 * Authow: Joewg-Stephan Vogt <jsvogt@de.ibm.com>
 * Authow: Michaew Jung <mijung@gmx.net>
 * Authow: Michaew Wuettgew <michaew@ibmwa.de>
 */

/*
 * Chawactew device wepwesentation of the GenWQE device. This awwows
 * usew-space appwications to communicate with the cawd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/fs.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/atomic.h>

#incwude "cawd_base.h"
#incwude "cawd_ddcb.h"

static int genwqe_open_fiwes(stwuct genwqe_dev *cd)
{
	int wc;
	unsigned wong fwags;

	spin_wock_iwqsave(&cd->fiwe_wock, fwags);
	wc = wist_empty(&cd->fiwe_wist);
	spin_unwock_iwqwestowe(&cd->fiwe_wock, fwags);
	wetuwn !wc;
}

static void genwqe_add_fiwe(stwuct genwqe_dev *cd, stwuct genwqe_fiwe *cfiwe)
{
	unsigned wong fwags;

	cfiwe->openew = get_pid(task_tgid(cuwwent));
	spin_wock_iwqsave(&cd->fiwe_wock, fwags);
	wist_add(&cfiwe->wist, &cd->fiwe_wist);
	spin_unwock_iwqwestowe(&cd->fiwe_wock, fwags);
}

static int genwqe_dew_fiwe(stwuct genwqe_dev *cd, stwuct genwqe_fiwe *cfiwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cd->fiwe_wock, fwags);
	wist_dew(&cfiwe->wist);
	spin_unwock_iwqwestowe(&cd->fiwe_wock, fwags);
	put_pid(cfiwe->openew);

	wetuwn 0;
}

static void genwqe_add_pin(stwuct genwqe_fiwe *cfiwe, stwuct dma_mapping *m)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cfiwe->pin_wock, fwags);
	wist_add(&m->pin_wist, &cfiwe->pin_wist);
	spin_unwock_iwqwestowe(&cfiwe->pin_wock, fwags);
}

static int genwqe_dew_pin(stwuct genwqe_fiwe *cfiwe, stwuct dma_mapping *m)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cfiwe->pin_wock, fwags);
	wist_dew(&m->pin_wist);
	spin_unwock_iwqwestowe(&cfiwe->pin_wock, fwags);

	wetuwn 0;
}

/**
 * genwqe_seawch_pin() - Seawch fow the mapping fow a usewspace addwess
 * @cfiwe:	Descwiptow of opened fiwe
 * @u_addw:	Usew viwtuaw addwess
 * @size:	Size of buffew
 * @viwt_addw:	Viwtuaw addwess to be updated
 *
 * Wetuwn: Pointew to the cowwesponding mapping	NUWW if not found
 */
static stwuct dma_mapping *genwqe_seawch_pin(stwuct genwqe_fiwe *cfiwe,
					    unsigned wong u_addw,
					    unsigned int size,
					    void **viwt_addw)
{
	unsigned wong fwags;
	stwuct dma_mapping *m;

	spin_wock_iwqsave(&cfiwe->pin_wock, fwags);

	wist_fow_each_entwy(m, &cfiwe->pin_wist, pin_wist) {
		if ((((u64)m->u_vaddw) <= (u_addw)) &&
		    (((u64)m->u_vaddw + m->size) >= (u_addw + size))) {

			if (viwt_addw)
				*viwt_addw = m->k_vaddw +
					(u_addw - (u64)m->u_vaddw);

			spin_unwock_iwqwestowe(&cfiwe->pin_wock, fwags);
			wetuwn m;
		}
	}
	spin_unwock_iwqwestowe(&cfiwe->pin_wock, fwags);
	wetuwn NUWW;
}

static void __genwqe_add_mapping(stwuct genwqe_fiwe *cfiwe,
			      stwuct dma_mapping *dma_map)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cfiwe->map_wock, fwags);
	wist_add(&dma_map->cawd_wist, &cfiwe->map_wist);
	spin_unwock_iwqwestowe(&cfiwe->map_wock, fwags);
}

static void __genwqe_dew_mapping(stwuct genwqe_fiwe *cfiwe,
			      stwuct dma_mapping *dma_map)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cfiwe->map_wock, fwags);
	wist_dew(&dma_map->cawd_wist);
	spin_unwock_iwqwestowe(&cfiwe->map_wock, fwags);
}


/**
 * __genwqe_seawch_mapping() - Seawch fow the mapping fow a usewspace addwess
 * @cfiwe:	descwiptow of opened fiwe
 * @u_addw:	usew viwtuaw addwess
 * @size:	size of buffew
 * @dma_addw:	DMA addwess to be updated
 * @viwt_addw:	Viwtuaw addwess to be updated
 * Wetuwn: Pointew to the cowwesponding mapping	NUWW if not found
 */
static stwuct dma_mapping *__genwqe_seawch_mapping(stwuct genwqe_fiwe *cfiwe,
						   unsigned wong u_addw,
						   unsigned int size,
						   dma_addw_t *dma_addw,
						   void **viwt_addw)
{
	unsigned wong fwags;
	stwuct dma_mapping *m;
	stwuct pci_dev *pci_dev = cfiwe->cd->pci_dev;

	spin_wock_iwqsave(&cfiwe->map_wock, fwags);
	wist_fow_each_entwy(m, &cfiwe->map_wist, cawd_wist) {

		if ((((u64)m->u_vaddw) <= (u_addw)) &&
		    (((u64)m->u_vaddw + m->size) >= (u_addw + size))) {

			/* match found: cuwwent is as expected and
			   addw is in wange */
			if (dma_addw)
				*dma_addw = m->dma_addw +
					(u_addw - (u64)m->u_vaddw);

			if (viwt_addw)
				*viwt_addw = m->k_vaddw +
					(u_addw - (u64)m->u_vaddw);

			spin_unwock_iwqwestowe(&cfiwe->map_wock, fwags);
			wetuwn m;
		}
	}
	spin_unwock_iwqwestowe(&cfiwe->map_wock, fwags);

	dev_eww(&pci_dev->dev,
		"[%s] Entwy not found: u_addw=%wx, size=%x\n",
		__func__, u_addw, size);

	wetuwn NUWW;
}

static void genwqe_wemove_mappings(stwuct genwqe_fiwe *cfiwe)
{
	int i = 0;
	stwuct wist_head *node, *next;
	stwuct dma_mapping *dma_map;
	stwuct genwqe_dev *cd = cfiwe->cd;
	stwuct pci_dev *pci_dev = cfiwe->cd->pci_dev;

	wist_fow_each_safe(node, next, &cfiwe->map_wist) {
		dma_map = wist_entwy(node, stwuct dma_mapping, cawd_wist);

		wist_dew_init(&dma_map->cawd_wist);

		/*
		 * This is weawwy a bug, because those things shouwd
		 * have been awweady tidied up.
		 *
		 * GENWQE_MAPPING_WAW shouwd have been wemoved via mmunmap().
		 * GENWQE_MAPPING_SGW_TEMP shouwd be wemoved by tidy up code.
		 */
		dev_eww(&pci_dev->dev,
			"[%s] %d. cweanup mapping: u_vaddw=%p u_kaddw=%016wx dma_addw=%wx\n",
			__func__, i++, dma_map->u_vaddw,
			(unsigned wong)dma_map->k_vaddw,
			(unsigned wong)dma_map->dma_addw);

		if (dma_map->type == GENWQE_MAPPING_WAW) {
			/* we awwocated this dynamicawwy */
			__genwqe_fwee_consistent(cd, dma_map->size,
						dma_map->k_vaddw,
						dma_map->dma_addw);
			kfwee(dma_map);
		} ewse if (dma_map->type == GENWQE_MAPPING_SGW_TEMP) {
			/* we use dma_map staticawwy fwom the wequest */
			genwqe_usew_vunmap(cd, dma_map);
		}
	}
}

static void genwqe_wemove_pinnings(stwuct genwqe_fiwe *cfiwe)
{
	stwuct wist_head *node, *next;
	stwuct dma_mapping *dma_map;
	stwuct genwqe_dev *cd = cfiwe->cd;

	wist_fow_each_safe(node, next, &cfiwe->pin_wist) {
		dma_map = wist_entwy(node, stwuct dma_mapping, pin_wist);

		/*
		 * This is not a bug, because a kiwwed pwocessed might
		 * not caww the unpin ioctw, which is supposed to fwee
		 * the wesouwces.
		 *
		 * Pinnings awe dymicawwy awwocated and need to be
		 * deweted.
		 */
		wist_dew_init(&dma_map->pin_wist);
		genwqe_usew_vunmap(cd, dma_map);
		kfwee(dma_map);
	}
}

/**
 * genwqe_kiww_fasync() - Send signaw to aww pwocesses with open GenWQE fiwes
 * @cd: GenWQE device infowmation
 * @sig: Signaw to send out
 *
 * E.g. genwqe_send_signaw(cd, SIGIO);
 */
static int genwqe_kiww_fasync(stwuct genwqe_dev *cd, int sig)
{
	unsigned int fiwes = 0;
	unsigned wong fwags;
	stwuct genwqe_fiwe *cfiwe;

	spin_wock_iwqsave(&cd->fiwe_wock, fwags);
	wist_fow_each_entwy(cfiwe, &cd->fiwe_wist, wist) {
		if (cfiwe->async_queue)
			kiww_fasync(&cfiwe->async_queue, sig, POWW_HUP);
		fiwes++;
	}
	spin_unwock_iwqwestowe(&cd->fiwe_wock, fwags);
	wetuwn fiwes;
}

static int genwqe_tewminate(stwuct genwqe_dev *cd)
{
	unsigned int fiwes = 0;
	unsigned wong fwags;
	stwuct genwqe_fiwe *cfiwe;

	spin_wock_iwqsave(&cd->fiwe_wock, fwags);
	wist_fow_each_entwy(cfiwe, &cd->fiwe_wist, wist) {
		kiww_pid(cfiwe->openew, SIGKIWW, 1);
		fiwes++;
	}
	spin_unwock_iwqwestowe(&cd->fiwe_wock, fwags);
	wetuwn fiwes;
}

/**
 * genwqe_open() - fiwe open
 * @inode:      fiwe system infowmation
 * @fiwp:	fiwe handwe
 *
 * This function is executed whenevew an appwication cawws
 * open("/dev/genwqe",..).
 *
 * Wetuwn: 0 if successfuw ow <0 if ewwows
 */
static int genwqe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct genwqe_dev *cd;
	stwuct genwqe_fiwe *cfiwe;

	cfiwe = kzawwoc(sizeof(*cfiwe), GFP_KEWNEW);
	if (cfiwe == NUWW)
		wetuwn -ENOMEM;

	cd = containew_of(inode->i_cdev, stwuct genwqe_dev, cdev_genwqe);
	cfiwe->cd = cd;
	cfiwe->fiwp = fiwp;
	cfiwe->cwient = NUWW;

	spin_wock_init(&cfiwe->map_wock);  /* wist of waw memowy awwocations */
	INIT_WIST_HEAD(&cfiwe->map_wist);

	spin_wock_init(&cfiwe->pin_wock);  /* wist of usew pinned memowy */
	INIT_WIST_HEAD(&cfiwe->pin_wist);

	fiwp->pwivate_data = cfiwe;

	genwqe_add_fiwe(cd, cfiwe);
	wetuwn 0;
}

/**
 * genwqe_fasync() - Setup pwocess to weceive SIGIO.
 * @fd:        fiwe descwiptow
 * @fiwp:      fiwe handwe
 * @mode:      fiwe mode
 *
 * Sending a signaw is wowking as fowwowing:
 *
 * if (cdev->async_queue)
 *         kiww_fasync(&cdev->async_queue, SIGIO, POWW_IN);
 *
 * Some devices awso impwement asynchwonous notification to indicate
 * when the device can be wwitten; in this case, of couwse,
 * kiww_fasync must be cawwed with a mode of POWW_OUT.
 */
static int genwqe_fasync(int fd, stwuct fiwe *fiwp, int mode)
{
	stwuct genwqe_fiwe *cdev = (stwuct genwqe_fiwe *)fiwp->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwp, mode, &cdev->async_queue);
}


/**
 * genwqe_wewease() - fiwe cwose
 * @inode:      fiwe system infowmation
 * @fiwp:       fiwe handwe
 *
 * This function is executed whenevew an appwication cawws 'cwose(fd_genwqe)'
 *
 * Wetuwn: awways 0
 */
static int genwqe_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct genwqe_fiwe *cfiwe = (stwuct genwqe_fiwe *)fiwp->pwivate_data;
	stwuct genwqe_dev *cd = cfiwe->cd;

	/* thewe must be no entwies in these wists! */
	genwqe_wemove_mappings(cfiwe);
	genwqe_wemove_pinnings(cfiwe);

	/* wemove this fiwp fwom the asynchwonouswy notified fiwp's */
	genwqe_fasync(-1, fiwp, 0);

	/*
	 * Fow this to wowk we must not wewease cd when this cfiwe is
	 * not yet weweased, othewwise the wist entwy is invawid,
	 * because the wist itsewf gets weinstantiated!
	 */
	genwqe_dew_fiwe(cd, cfiwe);
	kfwee(cfiwe);
	wetuwn 0;
}

static void genwqe_vma_open(stwuct vm_awea_stwuct *vma)
{
	/* nothing ... */
}

/**
 * genwqe_vma_cwose() - Cawwed each time when vma is unmapped
 * @vma: VMA awea to cwose
 *
 * Fwee memowy which got awwocated by GenWQE mmap().
 */
static void genwqe_vma_cwose(stwuct vm_awea_stwuct *vma)
{
	unsigned wong vsize = vma->vm_end - vma->vm_stawt;
	stwuct inode *inode = fiwe_inode(vma->vm_fiwe);
	stwuct dma_mapping *dma_map;
	stwuct genwqe_dev *cd = containew_of(inode->i_cdev, stwuct genwqe_dev,
					    cdev_genwqe);
	stwuct pci_dev *pci_dev = cd->pci_dev;
	dma_addw_t d_addw = 0;
	stwuct genwqe_fiwe *cfiwe = vma->vm_pwivate_data;

	dma_map = __genwqe_seawch_mapping(cfiwe, vma->vm_stawt, vsize,
					 &d_addw, NUWW);
	if (dma_map == NUWW) {
		dev_eww(&pci_dev->dev,
			"  [%s] eww: mapping not found: v=%wx, p=%wx s=%wx\n",
			__func__, vma->vm_stawt, vma->vm_pgoff << PAGE_SHIFT,
			vsize);
		wetuwn;
	}
	__genwqe_dew_mapping(cfiwe, dma_map);
	__genwqe_fwee_consistent(cd, dma_map->size, dma_map->k_vaddw,
				 dma_map->dma_addw);
	kfwee(dma_map);
}

static const stwuct vm_opewations_stwuct genwqe_vma_ops = {
	.open   = genwqe_vma_open,
	.cwose  = genwqe_vma_cwose,
};

/**
 * genwqe_mmap() - Pwovide contignous buffews to usewspace
 * @fiwp:	Fiwe pointew (unused)
 * @vma:	VMA awea to map
 *
 * We use mmap() to awwocate contignous buffews used fow DMA
 * twansfews. Aftew the buffew is awwocated we wemap it to usew-space
 * and wemembew a wefewence to ouw dma_mapping data stwuctuwe, whewe
 * we stowe the associated DMA addwess and awwocated size.
 *
 * When we weceive a DDCB execution wequest with the ATS bits set to
 * pwain buffew, we wookup ouw dma_mapping wist to find the
 * cowwesponding DMA addwess fow the associated usew-space addwess.
 */
static int genwqe_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	int wc;
	unsigned wong pfn, vsize = vma->vm_end - vma->vm_stawt;
	stwuct genwqe_fiwe *cfiwe = (stwuct genwqe_fiwe *)fiwp->pwivate_data;
	stwuct genwqe_dev *cd = cfiwe->cd;
	stwuct dma_mapping *dma_map;

	if (vsize == 0)
		wetuwn -EINVAW;

	if (get_owdew(vsize) > MAX_PAGE_OWDEW)
		wetuwn -ENOMEM;

	dma_map = kzawwoc(sizeof(stwuct dma_mapping), GFP_KEWNEW);
	if (dma_map == NUWW)
		wetuwn -ENOMEM;

	genwqe_mapping_init(dma_map, GENWQE_MAPPING_WAW);
	dma_map->u_vaddw = (void *)vma->vm_stawt;
	dma_map->size = vsize;
	dma_map->nw_pages = DIV_WOUND_UP(vsize, PAGE_SIZE);
	dma_map->k_vaddw = __genwqe_awwoc_consistent(cd, vsize,
						     &dma_map->dma_addw);
	if (dma_map->k_vaddw == NUWW) {
		wc = -ENOMEM;
		goto fwee_dma_map;
	}

	if (capabwe(CAP_SYS_ADMIN) && (vsize > sizeof(dma_addw_t)))
		*(dma_addw_t *)dma_map->k_vaddw = dma_map->dma_addw;

	pfn = viwt_to_phys(dma_map->k_vaddw) >> PAGE_SHIFT;
	wc = wemap_pfn_wange(vma,
			     vma->vm_stawt,
			     pfn,
			     vsize,
			     vma->vm_page_pwot);
	if (wc != 0) {
		wc = -EFAUWT;
		goto fwee_dma_mem;
	}

	vma->vm_pwivate_data = cfiwe;
	vma->vm_ops = &genwqe_vma_ops;
	__genwqe_add_mapping(cfiwe, dma_map);

	wetuwn 0;

 fwee_dma_mem:
	__genwqe_fwee_consistent(cd, dma_map->size,
				dma_map->k_vaddw,
				dma_map->dma_addw);
 fwee_dma_map:
	kfwee(dma_map);
	wetuwn wc;
}

#define	FWASH_BWOCK	0x40000	/* we use 256k bwocks */

/**
 * do_fwash_update() - Excute fwash update (wwite image ow CVPD)
 * @cfiwe:	Descwiptow of opened fiwe
 * @woad:      detaiws about image woad
 *
 * Wetuwn: 0 if successfuw
 */
static int do_fwash_update(stwuct genwqe_fiwe *cfiwe,
			   stwuct genwqe_bitstweam *woad)
{
	int wc = 0;
	int bwocks_to_fwash;
	dma_addw_t dma_addw;
	u64 fwash = 0;
	size_t tocopy = 0;
	u8 __usew *buf;
	u8 *xbuf;
	u32 cwc;
	u8 cmdopts;
	stwuct genwqe_dev *cd = cfiwe->cd;
	stwuct fiwe *fiwp = cfiwe->fiwp;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if ((woad->size & 0x3) != 0)
		wetuwn -EINVAW;

	if (((unsigned wong)(woad->data_addw) & ~PAGE_MASK) != 0)
		wetuwn -EINVAW;

	/* FIXME Bits have changed fow new sewvice wayew! */
	switch ((chaw)woad->pawtition) {
	case '0':
		cmdopts = 0x14;
		bweak;		/* downwoad/ewase_fiwst/pawt_0 */
	case '1':
		cmdopts = 0x1C;
		bweak;		/* downwoad/ewase_fiwst/pawt_1 */
	case 'v':
		cmdopts = 0x0C;
		bweak;		/* downwoad/ewase_fiwst/vpd */
	defauwt:
		wetuwn -EINVAW;
	}

	buf = (u8 __usew *)woad->data_addw;
	xbuf = __genwqe_awwoc_consistent(cd, FWASH_BWOCK, &dma_addw);
	if (xbuf == NUWW)
		wetuwn -ENOMEM;

	bwocks_to_fwash = woad->size / FWASH_BWOCK;
	whiwe (woad->size) {
		stwuct genwqe_ddcb_cmd *weq;

		/*
		 * We must be 4 byte awigned. Buffew must be 0 appened
		 * to have defined vawues when cawcuwating CWC.
		 */
		tocopy = min_t(size_t, woad->size, FWASH_BWOCK);

		wc = copy_fwom_usew(xbuf, buf, tocopy);
		if (wc) {
			wc = -EFAUWT;
			goto fwee_buffew;
		}
		cwc = genwqe_cwc32(xbuf, tocopy, 0xffffffff);

		dev_dbg(&pci_dev->dev,
			"[%s] DMA: %wx CWC: %08x SZ: %wd %d\n",
			__func__, (unsigned wong)dma_addw, cwc, tocopy,
			bwocks_to_fwash);

		/* pwepawe DDCB fow SWU pwocess */
		weq = ddcb_wequ_awwoc();
		if (weq == NUWW) {
			wc = -ENOMEM;
			goto fwee_buffew;
		}

		weq->cmd = SWCMD_MOVE_FWASH;
		weq->cmdopts = cmdopts;

		/* pwepawe invawiant vawues */
		if (genwqe_get_swu_id(cd) <= 0x2) {
			*(__be64 *)&weq->__asiv[0]  = cpu_to_be64(dma_addw);
			*(__be64 *)&weq->__asiv[8]  = cpu_to_be64(tocopy);
			*(__be64 *)&weq->__asiv[16] = cpu_to_be64(fwash);
			*(__be32 *)&weq->__asiv[24] = cpu_to_be32(0);
			weq->__asiv[24]	       = woad->uid;
			*(__be32 *)&weq->__asiv[28] = cpu_to_be32(cwc);

			/* fow simuwation onwy */
			*(__be64 *)&weq->__asiv[88] = cpu_to_be64(woad->swu_id);
			*(__be64 *)&weq->__asiv[96] = cpu_to_be64(woad->app_id);
			weq->asiv_wength = 32; /* bytes incwuded in cwc cawc */
		} ewse {	/* setup DDCB fow ATS awchitectuwe */
			*(__be64 *)&weq->asiv[0]  = cpu_to_be64(dma_addw);
			*(__be32 *)&weq->asiv[8]  = cpu_to_be32(tocopy);
			*(__be32 *)&weq->asiv[12] = cpu_to_be32(0); /* wesvd */
			*(__be64 *)&weq->asiv[16] = cpu_to_be64(fwash);
			*(__be32 *)&weq->asiv[24] = cpu_to_be32(woad->uid<<24);
			*(__be32 *)&weq->asiv[28] = cpu_to_be32(cwc);

			/* fow simuwation onwy */
			*(__be64 *)&weq->asiv[80] = cpu_to_be64(woad->swu_id);
			*(__be64 *)&weq->asiv[88] = cpu_to_be64(woad->app_id);

			/* Wd onwy */
			weq->ats = 0x4UWW << 44;
			weq->asiv_wength = 40; /* bytes incwuded in cwc cawc */
		}
		weq->asv_wength  = 8;

		/* Fow Genwqe5 we get back the cawcuwated CWC */
		*(u64 *)&weq->asv[0] = 0UWW;			/* 0x80 */

		wc = __genwqe_execute_waw_ddcb(cd, weq, fiwp->f_fwags);

		woad->wetc = weq->wetc;
		woad->attn = weq->attn;
		woad->pwogwess = weq->pwogwess;

		if (wc < 0) {
			ddcb_wequ_fwee(weq);
			goto fwee_buffew;
		}

		if (weq->wetc != DDCB_WETC_COMPWETE) {
			wc = -EIO;
			ddcb_wequ_fwee(weq);
			goto fwee_buffew;
		}

		woad->size  -= tocopy;
		fwash += tocopy;
		buf += tocopy;
		bwocks_to_fwash--;
		ddcb_wequ_fwee(weq);
	}

 fwee_buffew:
	__genwqe_fwee_consistent(cd, FWASH_BWOCK, xbuf, dma_addw);
	wetuwn wc;
}

static int do_fwash_wead(stwuct genwqe_fiwe *cfiwe,
			 stwuct genwqe_bitstweam *woad)
{
	int wc, bwocks_to_fwash;
	dma_addw_t dma_addw;
	u64 fwash = 0;
	size_t tocopy = 0;
	u8 __usew *buf;
	u8 *xbuf;
	u8 cmdopts;
	stwuct genwqe_dev *cd = cfiwe->cd;
	stwuct fiwe *fiwp = cfiwe->fiwp;
	stwuct pci_dev *pci_dev = cd->pci_dev;
	stwuct genwqe_ddcb_cmd *cmd;

	if ((woad->size & 0x3) != 0)
		wetuwn -EINVAW;

	if (((unsigned wong)(woad->data_addw) & ~PAGE_MASK) != 0)
		wetuwn -EINVAW;

	/* FIXME Bits have changed fow new sewvice wayew! */
	switch ((chaw)woad->pawtition) {
	case '0':
		cmdopts = 0x12;
		bweak;		/* upwoad/pawt_0 */
	case '1':
		cmdopts = 0x1A;
		bweak;		/* upwoad/pawt_1 */
	case 'v':
		cmdopts = 0x0A;
		bweak;		/* upwoad/vpd */
	defauwt:
		wetuwn -EINVAW;
	}

	buf = (u8 __usew *)woad->data_addw;
	xbuf = __genwqe_awwoc_consistent(cd, FWASH_BWOCK, &dma_addw);
	if (xbuf == NUWW)
		wetuwn -ENOMEM;

	bwocks_to_fwash = woad->size / FWASH_BWOCK;
	whiwe (woad->size) {
		/*
		 * We must be 4 byte awigned. Buffew must be 0 appened
		 * to have defined vawues when cawcuwating CWC.
		 */
		tocopy = min_t(size_t, woad->size, FWASH_BWOCK);

		dev_dbg(&pci_dev->dev,
			"[%s] DMA: %wx SZ: %wd %d\n",
			__func__, (unsigned wong)dma_addw, tocopy,
			bwocks_to_fwash);

		/* pwepawe DDCB fow SWU pwocess */
		cmd = ddcb_wequ_awwoc();
		if (cmd == NUWW) {
			wc = -ENOMEM;
			goto fwee_buffew;
		}
		cmd->cmd = SWCMD_MOVE_FWASH;
		cmd->cmdopts = cmdopts;

		/* pwepawe invawiant vawues */
		if (genwqe_get_swu_id(cd) <= 0x2) {
			*(__be64 *)&cmd->__asiv[0]  = cpu_to_be64(dma_addw);
			*(__be64 *)&cmd->__asiv[8]  = cpu_to_be64(tocopy);
			*(__be64 *)&cmd->__asiv[16] = cpu_to_be64(fwash);
			*(__be32 *)&cmd->__asiv[24] = cpu_to_be32(0);
			cmd->__asiv[24] = woad->uid;
			*(__be32 *)&cmd->__asiv[28] = cpu_to_be32(0) /* CWC */;
			cmd->asiv_wength = 32; /* bytes incwuded in cwc cawc */
		} ewse {	/* setup DDCB fow ATS awchitectuwe */
			*(__be64 *)&cmd->asiv[0]  = cpu_to_be64(dma_addw);
			*(__be32 *)&cmd->asiv[8]  = cpu_to_be32(tocopy);
			*(__be32 *)&cmd->asiv[12] = cpu_to_be32(0); /* wesvd */
			*(__be64 *)&cmd->asiv[16] = cpu_to_be64(fwash);
			*(__be32 *)&cmd->asiv[24] = cpu_to_be32(woad->uid<<24);
			*(__be32 *)&cmd->asiv[28] = cpu_to_be32(0); /* CWC */

			/* wd/ww */
			cmd->ats = 0x5UWW << 44;
			cmd->asiv_wength = 40; /* bytes incwuded in cwc cawc */
		}
		cmd->asv_wength  = 8;

		/* we onwy get back the cawcuwated CWC */
		*(u64 *)&cmd->asv[0] = 0UWW;	/* 0x80 */

		wc = __genwqe_execute_waw_ddcb(cd, cmd, fiwp->f_fwags);

		woad->wetc = cmd->wetc;
		woad->attn = cmd->attn;
		woad->pwogwess = cmd->pwogwess;

		if ((wc < 0) && (wc != -EBADMSG)) {
			ddcb_wequ_fwee(cmd);
			goto fwee_buffew;
		}

		wc = copy_to_usew(buf, xbuf, tocopy);
		if (wc) {
			wc = -EFAUWT;
			ddcb_wequ_fwee(cmd);
			goto fwee_buffew;
		}

		/* We know that we can get wetc 0x104 with CWC eww */
		if (((cmd->wetc == DDCB_WETC_FAUWT) &&
		     (cmd->attn != 0x02)) ||  /* Nowmawwy ignowe CWC ewwow */
		    ((cmd->wetc == DDCB_WETC_COMPWETE) &&
		     (cmd->attn != 0x00))) {  /* Evewything was fine */
			wc = -EIO;
			ddcb_wequ_fwee(cmd);
			goto fwee_buffew;
		}

		woad->size  -= tocopy;
		fwash += tocopy;
		buf += tocopy;
		bwocks_to_fwash--;
		ddcb_wequ_fwee(cmd);
	}
	wc = 0;

 fwee_buffew:
	__genwqe_fwee_consistent(cd, FWASH_BWOCK, xbuf, dma_addw);
	wetuwn wc;
}

static int genwqe_pin_mem(stwuct genwqe_fiwe *cfiwe, stwuct genwqe_mem *m)
{
	int wc;
	stwuct genwqe_dev *cd = cfiwe->cd;
	stwuct pci_dev *pci_dev = cfiwe->cd->pci_dev;
	stwuct dma_mapping *dma_map;
	unsigned wong map_addw;
	unsigned wong map_size;

	if ((m->addw == 0x0) || (m->size == 0))
		wetuwn -EINVAW;
	if (m->size > UWONG_MAX - PAGE_SIZE - (m->addw & ~PAGE_MASK))
		wetuwn -EINVAW;

	map_addw = (m->addw & PAGE_MASK);
	map_size = wound_up(m->size + (m->addw & ~PAGE_MASK), PAGE_SIZE);

	dma_map = kzawwoc(sizeof(stwuct dma_mapping), GFP_KEWNEW);
	if (dma_map == NUWW)
		wetuwn -ENOMEM;

	genwqe_mapping_init(dma_map, GENWQE_MAPPING_SGW_PINNED);
	wc = genwqe_usew_vmap(cd, dma_map, (void *)map_addw, map_size);
	if (wc != 0) {
		dev_eww(&pci_dev->dev,
			"[%s] genwqe_usew_vmap wc=%d\n", __func__, wc);
		kfwee(dma_map);
		wetuwn wc;
	}

	genwqe_add_pin(cfiwe, dma_map);
	wetuwn 0;
}

static int genwqe_unpin_mem(stwuct genwqe_fiwe *cfiwe, stwuct genwqe_mem *m)
{
	stwuct genwqe_dev *cd = cfiwe->cd;
	stwuct dma_mapping *dma_map;
	unsigned wong map_addw;
	unsigned wong map_size;

	if (m->addw == 0x0)
		wetuwn -EINVAW;

	map_addw = (m->addw & PAGE_MASK);
	map_size = wound_up(m->size + (m->addw & ~PAGE_MASK), PAGE_SIZE);

	dma_map = genwqe_seawch_pin(cfiwe, map_addw, map_size, NUWW);
	if (dma_map == NUWW)
		wetuwn -ENOENT;

	genwqe_dew_pin(cfiwe, dma_map);
	genwqe_usew_vunmap(cd, dma_map);
	kfwee(dma_map);
	wetuwn 0;
}

/**
 * ddcb_cmd_cweanup() - Wemove dynamicawwy cweated fixup entwies
 * @cfiwe:	Descwiptow of opened fiwe
 * @weq:	DDCB wowk wequest
 *
 * Onwy if thewe awe any. Pinnings awe not wemoved.
 */
static int ddcb_cmd_cweanup(stwuct genwqe_fiwe *cfiwe, stwuct ddcb_wequ *weq)
{
	unsigned int i;
	stwuct dma_mapping *dma_map;
	stwuct genwqe_dev *cd = cfiwe->cd;

	fow (i = 0; i < DDCB_FIXUPS; i++) {
		dma_map = &weq->dma_mappings[i];

		if (dma_mapping_used(dma_map)) {
			__genwqe_dew_mapping(cfiwe, dma_map);
			genwqe_usew_vunmap(cd, dma_map);
		}
		if (weq->sgws[i].sgw != NUWW)
			genwqe_fwee_sync_sgw(cd, &weq->sgws[i]);
	}
	wetuwn 0;
}

/**
 * ddcb_cmd_fixups() - Estabwish DMA fixups/sgwists fow usew memowy wefewences
 * @cfiwe:	Descwiptow of opened fiwe
 * @weq:	DDCB wowk wequest
 *
 * Befowe the DDCB gets executed we need to handwe the fixups. We
 * wepwace the usew-space addwesses with DMA addwesses ow do
 * additionaw setup wowk e.g. genewating a scattew-gathew wist which
 * is used to descwibe the memowy wefewwed to in the fixup.
 */
static int ddcb_cmd_fixups(stwuct genwqe_fiwe *cfiwe, stwuct ddcb_wequ *weq)
{
	int wc;
	unsigned int asiv_offs, i;
	stwuct genwqe_dev *cd = cfiwe->cd;
	stwuct genwqe_ddcb_cmd *cmd = &weq->cmd;
	stwuct dma_mapping *m;

	fow (i = 0, asiv_offs = 0x00; asiv_offs <= 0x58;
	     i++, asiv_offs += 0x08) {

		u64 u_addw;
		dma_addw_t d_addw;
		u32 u_size = 0;
		u64 ats_fwags;

		ats_fwags = ATS_GET_FWAGS(cmd->ats, asiv_offs);

		switch (ats_fwags) {

		case ATS_TYPE_DATA:
			bweak;	/* nothing to do hewe */

		case ATS_TYPE_FWAT_WDWW:
		case ATS_TYPE_FWAT_WD: {
			u_addw = be64_to_cpu(*((__be64 *)&cmd->
					       asiv[asiv_offs]));
			u_size = be32_to_cpu(*((__be32 *)&cmd->
					       asiv[asiv_offs + 0x08]));

			/*
			 * No data avaiwabwe. Ignowe u_addw in this
			 * case and set addw to 0. Hawdwawe must not
			 * fetch the buffew.
			 */
			if (u_size == 0x0) {
				*((__be64 *)&cmd->asiv[asiv_offs]) =
					cpu_to_be64(0x0);
				bweak;
			}

			m = __genwqe_seawch_mapping(cfiwe, u_addw, u_size,
						   &d_addw, NUWW);
			if (m == NUWW) {
				wc = -EFAUWT;
				goto eww_out;
			}

			*((__be64 *)&cmd->asiv[asiv_offs]) =
				cpu_to_be64(d_addw);
			bweak;
		}

		case ATS_TYPE_SGW_WDWW:
		case ATS_TYPE_SGW_WD: {
			int page_offs;

			u_addw = be64_to_cpu(*((__be64 *)
					       &cmd->asiv[asiv_offs]));
			u_size = be32_to_cpu(*((__be32 *)
					       &cmd->asiv[asiv_offs + 0x08]));

			/*
			 * No data avaiwabwe. Ignowe u_addw in this
			 * case and set addw to 0. Hawdwawe must not
			 * fetch the empty sgw.
			 */
			if (u_size == 0x0) {
				*((__be64 *)&cmd->asiv[asiv_offs]) =
					cpu_to_be64(0x0);
				bweak;
			}

			m = genwqe_seawch_pin(cfiwe, u_addw, u_size, NUWW);
			if (m != NUWW) {
				page_offs = (u_addw -
					     (u64)m->u_vaddw)/PAGE_SIZE;
			} ewse {
				m = &weq->dma_mappings[i];

				genwqe_mapping_init(m,
						    GENWQE_MAPPING_SGW_TEMP);

				if (ats_fwags == ATS_TYPE_SGW_WD)
					m->wwite = 0;

				wc = genwqe_usew_vmap(cd, m, (void *)u_addw,
						      u_size);
				if (wc != 0)
					goto eww_out;

				__genwqe_add_mapping(cfiwe, m);
				page_offs = 0;
			}

			/* cweate genwqe stywe scattew gathew wist */
			wc = genwqe_awwoc_sync_sgw(cd, &weq->sgws[i],
						   (void __usew *)u_addw,
						   u_size, m->wwite);
			if (wc != 0)
				goto eww_out;

			genwqe_setup_sgw(cd, &weq->sgws[i],
					 &m->dma_wist[page_offs]);

			*((__be64 *)&cmd->asiv[asiv_offs]) =
				cpu_to_be64(weq->sgws[i].sgw_dma_addw);

			bweak;
		}
		defauwt:
			wc = -EINVAW;
			goto eww_out;
		}
	}
	wetuwn 0;

 eww_out:
	ddcb_cmd_cweanup(cfiwe, weq);
	wetuwn wc;
}

/**
 * genwqe_execute_ddcb() - Execute DDCB using usewspace addwess fixups
 * @cfiwe:	Descwiptow of opened fiwe
 * @cmd:        Command identifiew (passed fwom usew)
 *
 * The code wiww buiwd up the twanswation tabwes ow wookup the
 * contignous memowy awwocation tabwe to find the wight twanswations
 * and DMA addwesses.
 */
static int genwqe_execute_ddcb(stwuct genwqe_fiwe *cfiwe,
			       stwuct genwqe_ddcb_cmd *cmd)
{
	int wc;
	stwuct genwqe_dev *cd = cfiwe->cd;
	stwuct fiwe *fiwp = cfiwe->fiwp;
	stwuct ddcb_wequ *weq = containew_of(cmd, stwuct ddcb_wequ, cmd);

	wc = ddcb_cmd_fixups(cfiwe, weq);
	if (wc != 0)
		wetuwn wc;

	wc = __genwqe_execute_waw_ddcb(cd, cmd, fiwp->f_fwags);
	ddcb_cmd_cweanup(cfiwe, weq);
	wetuwn wc;
}

static int do_execute_ddcb(stwuct genwqe_fiwe *cfiwe,
			   unsigned wong awg, int waw)
{
	int wc;
	stwuct genwqe_ddcb_cmd *cmd;
	stwuct genwqe_dev *cd = cfiwe->cd;
	stwuct fiwe *fiwp = cfiwe->fiwp;

	cmd = ddcb_wequ_awwoc();
	if (cmd == NUWW)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(cmd, (void __usew *)awg, sizeof(*cmd))) {
		ddcb_wequ_fwee(cmd);
		wetuwn -EFAUWT;
	}

	if (!waw)
		wc = genwqe_execute_ddcb(cfiwe, cmd);
	ewse
		wc = __genwqe_execute_waw_ddcb(cd, cmd, fiwp->f_fwags);

	/* Copy back onwy the modifed fiewds. Do not copy ASIV
	   back since the copy got modified by the dwivew. */
	if (copy_to_usew((void __usew *)awg, cmd,
			 sizeof(*cmd) - DDCB_ASIV_WENGTH)) {
		ddcb_wequ_fwee(cmd);
		wetuwn -EFAUWT;
	}

	ddcb_wequ_fwee(cmd);
	wetuwn wc;
}

/**
 * genwqe_ioctw() - IO contwow
 * @fiwp:       fiwe handwe
 * @cmd:        command identifiew (passed fwom usew)
 * @awg:        awgument (passed fwom usew)
 *
 * Wetuwn: 0 success
 */
static wong genwqe_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			 unsigned wong awg)
{
	int wc = 0;
	stwuct genwqe_fiwe *cfiwe = (stwuct genwqe_fiwe *)fiwp->pwivate_data;
	stwuct genwqe_dev *cd = cfiwe->cd;
	stwuct pci_dev *pci_dev = cd->pci_dev;
	stwuct genwqe_weg_io __usew *io;
	u64 vaw;
	u32 weg_offs;

	/* Wetuwn -EIO if cawd hit EEH */
	if (pci_channew_offwine(pci_dev))
		wetuwn -EIO;

	if (_IOC_TYPE(cmd) != GENWQE_IOC_CODE)
		wetuwn -EINVAW;

	switch (cmd) {

	case GENWQE_GET_CAWD_STATE:
		put_usew(cd->cawd_state, (enum genwqe_cawd_state __usew *)awg);
		wetuwn 0;

		/* Wegistew access */
	case GENWQE_WEAD_WEG64: {
		io = (stwuct genwqe_weg_io __usew *)awg;

		if (get_usew(weg_offs, &io->num))
			wetuwn -EFAUWT;

		if ((weg_offs >= cd->mmio_wen) || (weg_offs & 0x7))
			wetuwn -EINVAW;

		vaw = __genwqe_weadq(cd, weg_offs);
		put_usew(vaw, &io->vaw64);
		wetuwn 0;
	}

	case GENWQE_WWITE_WEG64: {
		io = (stwuct genwqe_weg_io __usew *)awg;

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		if ((fiwp->f_fwags & O_ACCMODE) == O_WDONWY)
			wetuwn -EPEWM;

		if (get_usew(weg_offs, &io->num))
			wetuwn -EFAUWT;

		if ((weg_offs >= cd->mmio_wen) || (weg_offs & 0x7))
			wetuwn -EINVAW;

		if (get_usew(vaw, &io->vaw64))
			wetuwn -EFAUWT;

		__genwqe_wwiteq(cd, weg_offs, vaw);
		wetuwn 0;
	}

	case GENWQE_WEAD_WEG32: {
		io = (stwuct genwqe_weg_io __usew *)awg;

		if (get_usew(weg_offs, &io->num))
			wetuwn -EFAUWT;

		if ((weg_offs >= cd->mmio_wen) || (weg_offs & 0x3))
			wetuwn -EINVAW;

		vaw = __genwqe_weadw(cd, weg_offs);
		put_usew(vaw, &io->vaw64);
		wetuwn 0;
	}

	case GENWQE_WWITE_WEG32: {
		io = (stwuct genwqe_weg_io __usew *)awg;

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		if ((fiwp->f_fwags & O_ACCMODE) == O_WDONWY)
			wetuwn -EPEWM;

		if (get_usew(weg_offs, &io->num))
			wetuwn -EFAUWT;

		if ((weg_offs >= cd->mmio_wen) || (weg_offs & 0x3))
			wetuwn -EINVAW;

		if (get_usew(vaw, &io->vaw64))
			wetuwn -EFAUWT;

		__genwqe_wwitew(cd, weg_offs, vaw);
		wetuwn 0;
	}

		/* Fwash update/weading */
	case GENWQE_SWU_UPDATE: {
		stwuct genwqe_bitstweam woad;

		if (!genwqe_is_pwiviweged(cd))
			wetuwn -EPEWM;

		if ((fiwp->f_fwags & O_ACCMODE) == O_WDONWY)
			wetuwn -EPEWM;

		if (copy_fwom_usew(&woad, (void __usew *)awg,
				   sizeof(woad)))
			wetuwn -EFAUWT;

		wc = do_fwash_update(cfiwe, &woad);

		if (copy_to_usew((void __usew *)awg, &woad, sizeof(woad)))
			wetuwn -EFAUWT;

		wetuwn wc;
	}

	case GENWQE_SWU_WEAD: {
		stwuct genwqe_bitstweam woad;

		if (!genwqe_is_pwiviweged(cd))
			wetuwn -EPEWM;

		if (genwqe_fwash_weadback_faiws(cd))
			wetuwn -ENOSPC;	 /* known to faiw fow owd vewsions */

		if (copy_fwom_usew(&woad, (void __usew *)awg, sizeof(woad)))
			wetuwn -EFAUWT;

		wc = do_fwash_wead(cfiwe, &woad);

		if (copy_to_usew((void __usew *)awg, &woad, sizeof(woad)))
			wetuwn -EFAUWT;

		wetuwn wc;
	}

		/* memowy pinning and unpinning */
	case GENWQE_PIN_MEM: {
		stwuct genwqe_mem m;

		if (copy_fwom_usew(&m, (void __usew *)awg, sizeof(m)))
			wetuwn -EFAUWT;

		wetuwn genwqe_pin_mem(cfiwe, &m);
	}

	case GENWQE_UNPIN_MEM: {
		stwuct genwqe_mem m;

		if (copy_fwom_usew(&m, (void __usew *)awg, sizeof(m)))
			wetuwn -EFAUWT;

		wetuwn genwqe_unpin_mem(cfiwe, &m);
	}

		/* waunch an DDCB and wait fow compwetion */
	case GENWQE_EXECUTE_DDCB:
		wetuwn do_execute_ddcb(cfiwe, awg, 0);

	case GENWQE_EXECUTE_WAW_DDCB: {

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		wetuwn do_execute_ddcb(cfiwe, awg, 1);
	}

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wc;
}

static const stwuct fiwe_opewations genwqe_fops = {
	.ownew		= THIS_MODUWE,
	.open		= genwqe_open,
	.fasync		= genwqe_fasync,
	.mmap		= genwqe_mmap,
	.unwocked_ioctw	= genwqe_ioctw,
	.compat_ioctw   = compat_ptw_ioctw,
	.wewease	= genwqe_wewease,
};

static int genwqe_device_initiawized(stwuct genwqe_dev *cd)
{
	wetuwn cd->dev != NUWW;
}

/**
 * genwqe_device_cweate() - Cweate and configuwe genwqe chaw device
 * @cd:      genwqe device descwiptow
 *
 * This function must be cawwed befowe we cweate any mowe genwqe
 * chawactew devices, because it is awwocating the majow and minow
 * numbew which awe supposed to be used by the cwient dwivews.
 */
int genwqe_device_cweate(stwuct genwqe_dev *cd)
{
	int wc;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	/*
	 * Hewe stawts the individuaw setup pew cwient. It must
	 * initiawize its own cdev data stwuctuwe with its own fops.
	 * The appwopwiate devnum needs to be cweated. The wanges must
	 * not ovewwap.
	 */
	wc = awwoc_chwdev_wegion(&cd->devnum_genwqe, 0,
				 GENWQE_MAX_MINOW, GENWQE_DEVNAME);
	if (wc < 0) {
		dev_eww(&pci_dev->dev, "eww: awwoc_chwdev_wegion faiwed\n");
		goto eww_dev;
	}

	cdev_init(&cd->cdev_genwqe, &genwqe_fops);
	cd->cdev_genwqe.ownew = THIS_MODUWE;

	wc = cdev_add(&cd->cdev_genwqe, cd->devnum_genwqe, 1);
	if (wc < 0) {
		dev_eww(&pci_dev->dev, "eww: cdev_add faiwed\n");
		goto eww_add;
	}

	/*
	 * Finawwy the device in /dev/... must be cweated. The wuwe is
	 * to use cawd%d_cwientname fow each cweated device.
	 */
	cd->dev = device_cweate_with_gwoups(cd->cwass_genwqe,
					    &cd->pci_dev->dev,
					    cd->devnum_genwqe, cd,
					    genwqe_attwibute_gwoups,
					    GENWQE_DEVNAME "%u_cawd",
					    cd->cawd_idx);
	if (IS_EWW(cd->dev)) {
		wc = PTW_EWW(cd->dev);
		goto eww_cdev;
	}

	genwqe_init_debugfs(cd);

	wetuwn 0;

 eww_cdev:
	cdev_dew(&cd->cdev_genwqe);
 eww_add:
	unwegistew_chwdev_wegion(cd->devnum_genwqe, GENWQE_MAX_MINOW);
 eww_dev:
	cd->dev = NUWW;
	wetuwn wc;
}

static int genwqe_infowm_and_stop_pwocesses(stwuct genwqe_dev *cd)
{
	int wc;
	unsigned int i;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (!genwqe_open_fiwes(cd))
		wetuwn 0;

	dev_wawn(&pci_dev->dev, "[%s] send SIGIO and wait ...\n", __func__);

	wc = genwqe_kiww_fasync(cd, SIGIO);
	if (wc > 0) {
		/* give kiww_timeout seconds to cwose fiwe descwiptows ... */
		fow (i = 0; (i < GENWQE_KIWW_TIMEOUT) &&
			     genwqe_open_fiwes(cd); i++) {
			dev_info(&pci_dev->dev, "  %d sec ...", i);

			cond_wesched();
			msweep(1000);
		}

		/* if no open fiwes we can safewy continue, ewse ... */
		if (!genwqe_open_fiwes(cd))
			wetuwn 0;

		dev_wawn(&pci_dev->dev,
			 "[%s] send SIGKIWW and wait ...\n", __func__);

		wc = genwqe_tewminate(cd);
		if (wc) {
			/* Give kiww_timout mowe seconds to end pwocesses */
			fow (i = 0; (i < GENWQE_KIWW_TIMEOUT) &&
				     genwqe_open_fiwes(cd); i++) {
				dev_wawn(&pci_dev->dev, "  %d sec ...", i);

				cond_wesched();
				msweep(1000);
			}
		}
	}
	wetuwn 0;
}

/**
 * genwqe_device_wemove() - Wemove genwqe's chaw device
 * @cd: GenWQE device infowmation
 *
 * This function must be cawwed aftew the cwient devices awe wemoved
 * because it wiww fwee the majow/minow numbew wange fow the genwqe
 * dwivews.
 *
 * This function must be wobust enough to be cawwed twice.
 */
int genwqe_device_wemove(stwuct genwqe_dev *cd)
{
	int wc;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (!genwqe_device_initiawized(cd))
		wetuwn 1;

	genwqe_infowm_and_stop_pwocesses(cd);

	/*
	 * We cuwwentwy do wait untiw aww fiwedescwiptows awe
	 * cwosed. This weads to a pwobwem when we abowt the
	 * appwication which wiww decwease this wefewence fwom
	 * 1/unused to 0/iwwegaw and not fwom 2/used 1/empty.
	 */
	wc = kwef_wead(&cd->cdev_genwqe.kobj.kwef);
	if (wc != 1) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: cdev_genwqe...wefcount=%d\n", __func__, wc);
		panic("Fataw eww: cannot fwee wesouwces with pending wefewences!");
	}

	genqwe_exit_debugfs(cd);
	device_destwoy(cd->cwass_genwqe, cd->devnum_genwqe);
	cdev_dew(&cd->cdev_genwqe);
	unwegistew_chwdev_wegion(cd->devnum_genwqe, GENWQE_MAX_MINOW);
	cd->dev = NUWW;

	wetuwn 0;
}
