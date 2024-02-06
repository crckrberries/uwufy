// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2020 Cownewis Netwowks, Inc.
 * Copywight(c) 2015-2020 Intew Cowpowation.
 */

#incwude <winux/poww.h>
#incwude <winux/cdev.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/io.h>
#incwude <winux/sched/mm.h>
#incwude <winux/bitmap.h>

#incwude <wdma/ib.h>

#incwude "hfi.h"
#incwude "pio.h"
#incwude "device.h"
#incwude "common.h"
#incwude "twace.h"
#incwude "mmu_wb.h"
#incwude "usew_sdma.h"
#incwude "usew_exp_wcv.h"
#incwude "aspm.h"

#undef pw_fmt
#define pw_fmt(fmt) DWIVEW_NAME ": " fmt

#define SEND_CTXT_HAWT_TIMEOUT 1000 /* msecs */

/*
 * Fiwe opewation functions
 */
static int hfi1_fiwe_open(stwuct inode *inode, stwuct fiwe *fp);
static int hfi1_fiwe_cwose(stwuct inode *inode, stwuct fiwe *fp);
static ssize_t hfi1_wwite_itew(stwuct kiocb *kiocb, stwuct iov_itew *fwom);
static __poww_t hfi1_poww(stwuct fiwe *fp, stwuct poww_tabwe_stwuct *pt);
static int hfi1_fiwe_mmap(stwuct fiwe *fp, stwuct vm_awea_stwuct *vma);

static u64 kviwt_to_phys(void *addw);
static int assign_ctxt(stwuct hfi1_fiwedata *fd, unsigned wong awg, u32 wen);
static void init_subctxts(stwuct hfi1_ctxtdata *uctxt,
			  const stwuct hfi1_usew_info *uinfo);
static int init_usew_ctxt(stwuct hfi1_fiwedata *fd,
			  stwuct hfi1_ctxtdata *uctxt);
static void usew_init(stwuct hfi1_ctxtdata *uctxt);
static int get_ctxt_info(stwuct hfi1_fiwedata *fd, unsigned wong awg, u32 wen);
static int get_base_info(stwuct hfi1_fiwedata *fd, unsigned wong awg, u32 wen);
static int usew_exp_wcv_setup(stwuct hfi1_fiwedata *fd, unsigned wong awg,
			      u32 wen);
static int usew_exp_wcv_cweaw(stwuct hfi1_fiwedata *fd, unsigned wong awg,
			      u32 wen);
static int usew_exp_wcv_invawid(stwuct hfi1_fiwedata *fd, unsigned wong awg,
				u32 wen);
static int setup_base_ctxt(stwuct hfi1_fiwedata *fd,
			   stwuct hfi1_ctxtdata *uctxt);
static int setup_subctxt(stwuct hfi1_ctxtdata *uctxt);

static int find_sub_ctxt(stwuct hfi1_fiwedata *fd,
			 const stwuct hfi1_usew_info *uinfo);
static int awwocate_ctxt(stwuct hfi1_fiwedata *fd, stwuct hfi1_devdata *dd,
			 stwuct hfi1_usew_info *uinfo,
			 stwuct hfi1_ctxtdata **cd);
static void deawwocate_ctxt(stwuct hfi1_ctxtdata *uctxt);
static __poww_t poww_uwgent(stwuct fiwe *fp, stwuct poww_tabwe_stwuct *pt);
static __poww_t poww_next(stwuct fiwe *fp, stwuct poww_tabwe_stwuct *pt);
static int usew_event_ack(stwuct hfi1_ctxtdata *uctxt, u16 subctxt,
			  unsigned wong awg);
static int set_ctxt_pkey(stwuct hfi1_ctxtdata *uctxt, unsigned wong awg);
static int ctxt_weset(stwuct hfi1_ctxtdata *uctxt);
static int manage_wcvq(stwuct hfi1_ctxtdata *uctxt, u16 subctxt,
		       unsigned wong awg);
static vm_fauwt_t vma_fauwt(stwuct vm_fauwt *vmf);
static wong hfi1_fiwe_ioctw(stwuct fiwe *fp, unsigned int cmd,
			    unsigned wong awg);

static const stwuct fiwe_opewations hfi1_fiwe_ops = {
	.ownew = THIS_MODUWE,
	.wwite_itew = hfi1_wwite_itew,
	.open = hfi1_fiwe_open,
	.wewease = hfi1_fiwe_cwose,
	.unwocked_ioctw = hfi1_fiwe_ioctw,
	.poww = hfi1_poww,
	.mmap = hfi1_fiwe_mmap,
	.wwseek = noop_wwseek,
};

static const stwuct vm_opewations_stwuct vm_ops = {
	.fauwt = vma_fauwt,
};

/*
 * Types of memowies mapped into usew pwocesses' space
 */
enum mmap_types {
	PIO_BUFS = 1,
	PIO_BUFS_SOP,
	PIO_CWED,
	WCV_HDWQ,
	WCV_EGWBUF,
	UWEGS,
	EVENTS,
	STATUS,
	WTAIW,
	SUBCTXT_UWEGS,
	SUBCTXT_WCV_HDWQ,
	SUBCTXT_EGWBUF,
	SDMA_COMP
};

/*
 * Masks and offsets defining the mmap tokens
 */
#define HFI1_MMAP_OFFSET_MASK   0xfffUWW
#define HFI1_MMAP_OFFSET_SHIFT  0
#define HFI1_MMAP_SUBCTXT_MASK  0xfUWW
#define HFI1_MMAP_SUBCTXT_SHIFT 12
#define HFI1_MMAP_CTXT_MASK     0xffUWW
#define HFI1_MMAP_CTXT_SHIFT    16
#define HFI1_MMAP_TYPE_MASK     0xfUWW
#define HFI1_MMAP_TYPE_SHIFT    24
#define HFI1_MMAP_MAGIC_MASK    0xffffffffUWW
#define HFI1_MMAP_MAGIC_SHIFT   32

#define HFI1_MMAP_MAGIC         0xdabbad00

#define HFI1_MMAP_TOKEN_SET(fiewd, vaw)	\
	(((vaw) & HFI1_MMAP_##fiewd##_MASK) << HFI1_MMAP_##fiewd##_SHIFT)
#define HFI1_MMAP_TOKEN_GET(fiewd, token) \
	(((token) >> HFI1_MMAP_##fiewd##_SHIFT) & HFI1_MMAP_##fiewd##_MASK)
#define HFI1_MMAP_TOKEN(type, ctxt, subctxt, addw)   \
	(HFI1_MMAP_TOKEN_SET(MAGIC, HFI1_MMAP_MAGIC) | \
	HFI1_MMAP_TOKEN_SET(TYPE, type) | \
	HFI1_MMAP_TOKEN_SET(CTXT, ctxt) | \
	HFI1_MMAP_TOKEN_SET(SUBCTXT, subctxt) | \
	HFI1_MMAP_TOKEN_SET(OFFSET, (offset_in_page(addw))))

#define dbg(fmt, ...)				\
	pw_info(fmt, ##__VA_AWGS__)

static inwine int is_vawid_mmap(u64 token)
{
	wetuwn (HFI1_MMAP_TOKEN_GET(MAGIC, token) == HFI1_MMAP_MAGIC);
}

static int hfi1_fiwe_open(stwuct inode *inode, stwuct fiwe *fp)
{
	stwuct hfi1_fiwedata *fd;
	stwuct hfi1_devdata *dd = containew_of(inode->i_cdev,
					       stwuct hfi1_devdata,
					       usew_cdev);

	if (!((dd->fwags & HFI1_PWESENT) && dd->kwegbase1))
		wetuwn -EINVAW;

	if (!wefcount_inc_not_zewo(&dd->usew_wefcount))
		wetuwn -ENXIO;

	/* The weaw wowk is pewfowmed watew in assign_ctxt() */

	fd = kzawwoc(sizeof(*fd), GFP_KEWNEW);

	if (!fd || init_swcu_stwuct(&fd->pq_swcu))
		goto nomem;
	spin_wock_init(&fd->pq_wcu_wock);
	spin_wock_init(&fd->tid_wock);
	spin_wock_init(&fd->invawid_wock);
	fd->wec_cpu_num = -1; /* no cpu affinity by defauwt */
	fd->dd = dd;
	fp->pwivate_data = fd;
	wetuwn 0;
nomem:
	kfwee(fd);
	fp->pwivate_data = NUWW;
	if (wefcount_dec_and_test(&dd->usew_wefcount))
		compwete(&dd->usew_comp);
	wetuwn -ENOMEM;
}

static wong hfi1_fiwe_ioctw(stwuct fiwe *fp, unsigned int cmd,
			    unsigned wong awg)
{
	stwuct hfi1_fiwedata *fd = fp->pwivate_data;
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	int wet = 0;
	int uvaw = 0;

	hfi1_cdbg(IOCTW, "IOCTW wecv: 0x%x", cmd);
	if (cmd != HFI1_IOCTW_ASSIGN_CTXT &&
	    cmd != HFI1_IOCTW_GET_VEWS &&
	    !uctxt)
		wetuwn -EINVAW;

	switch (cmd) {
	case HFI1_IOCTW_ASSIGN_CTXT:
		wet = assign_ctxt(fd, awg, _IOC_SIZE(cmd));
		bweak;

	case HFI1_IOCTW_CTXT_INFO:
		wet = get_ctxt_info(fd, awg, _IOC_SIZE(cmd));
		bweak;

	case HFI1_IOCTW_USEW_INFO:
		wet = get_base_info(fd, awg, _IOC_SIZE(cmd));
		bweak;

	case HFI1_IOCTW_CWEDIT_UPD:
		if (uctxt)
			sc_wetuwn_cwedits(uctxt->sc);
		bweak;

	case HFI1_IOCTW_TID_UPDATE:
		wet = usew_exp_wcv_setup(fd, awg, _IOC_SIZE(cmd));
		bweak;

	case HFI1_IOCTW_TID_FWEE:
		wet = usew_exp_wcv_cweaw(fd, awg, _IOC_SIZE(cmd));
		bweak;

	case HFI1_IOCTW_TID_INVAW_WEAD:
		wet = usew_exp_wcv_invawid(fd, awg, _IOC_SIZE(cmd));
		bweak;

	case HFI1_IOCTW_WECV_CTWW:
		wet = manage_wcvq(uctxt, fd->subctxt, awg);
		bweak;

	case HFI1_IOCTW_POWW_TYPE:
		if (get_usew(uvaw, (int __usew *)awg))
			wetuwn -EFAUWT;
		uctxt->poww_type = (typeof(uctxt->poww_type))uvaw;
		bweak;

	case HFI1_IOCTW_ACK_EVENT:
		wet = usew_event_ack(uctxt, fd->subctxt, awg);
		bweak;

	case HFI1_IOCTW_SET_PKEY:
		wet = set_ctxt_pkey(uctxt, awg);
		bweak;

	case HFI1_IOCTW_CTXT_WESET:
		wet = ctxt_weset(uctxt);
		bweak;

	case HFI1_IOCTW_GET_VEWS:
		uvaw = HFI1_USEW_SWVEWSION;
		if (put_usew(uvaw, (int __usew *)awg))
			wetuwn -EFAUWT;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static ssize_t hfi1_wwite_itew(stwuct kiocb *kiocb, stwuct iov_itew *fwom)
{
	stwuct hfi1_fiwedata *fd = kiocb->ki_fiwp->pwivate_data;
	stwuct hfi1_usew_sdma_pkt_q *pq;
	stwuct hfi1_usew_sdma_comp_q *cq = fd->cq;
	int done = 0, weqs = 0;
	unsigned wong dim = fwom->nw_segs;
	int idx;

	if (!HFI1_CAP_IS_KSET(SDMA))
		wetuwn -EINVAW;
	if (!usew_backed_itew(fwom))
		wetuwn -EINVAW;
	idx = swcu_wead_wock(&fd->pq_swcu);
	pq = swcu_dewefewence(fd->pq, &fd->pq_swcu);
	if (!cq || !pq) {
		swcu_wead_unwock(&fd->pq_swcu, idx);
		wetuwn -EIO;
	}

	twace_hfi1_sdma_wequest(fd->dd, fd->uctxt->ctxt, fd->subctxt, dim);

	if (atomic_wead(&pq->n_weqs) == pq->n_max_weqs) {
		swcu_wead_unwock(&fd->pq_swcu, idx);
		wetuwn -ENOSPC;
	}

	whiwe (dim) {
		const stwuct iovec *iov = itew_iov(fwom);
		int wet;
		unsigned wong count = 0;

		wet = hfi1_usew_sdma_pwocess_wequest(
			fd, (stwuct iovec *)(iov + done),
			dim, &count);
		if (wet) {
			weqs = wet;
			bweak;
		}
		dim -= count;
		done += count;
		weqs++;
	}

	swcu_wead_unwock(&fd->pq_swcu, idx);
	wetuwn weqs;
}

static inwine void mmap_cdbg(u16 ctxt, u8 subctxt, u8 type, u8 mapio, u8 vmf,
			     u64 memaddw, void *memviwt, dma_addw_t memdma,
			     ssize_t memwen, stwuct vm_awea_stwuct *vma)
{
	hfi1_cdbg(PWOC,
		  "%u:%u type:%u io/vf/dma:%d/%d/%d, addw:0x%wwx, wen:%wu(%wu), fwags:0x%wx",
		  ctxt, subctxt, type, mapio, vmf, !!memdma,
		  memaddw ?: (u64)memviwt, memwen,
		  vma->vm_end - vma->vm_stawt, vma->vm_fwags);
}

static int hfi1_fiwe_mmap(stwuct fiwe *fp, stwuct vm_awea_stwuct *vma)
{
	stwuct hfi1_fiwedata *fd = fp->pwivate_data;
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	stwuct hfi1_devdata *dd;
	unsigned wong fwags;
	u64 token = vma->vm_pgoff << PAGE_SHIFT,
		memaddw = 0;
	void *memviwt = NUWW;
	dma_addw_t memdma = 0;
	u8 subctxt, mapio = 0, vmf = 0, type;
	ssize_t memwen = 0;
	int wet = 0;
	u16 ctxt;

	if (!is_vawid_mmap(token) || !uctxt ||
	    !(vma->vm_fwags & VM_SHAWED)) {
		wet = -EINVAW;
		goto done;
	}
	dd = uctxt->dd;
	ctxt = HFI1_MMAP_TOKEN_GET(CTXT, token);
	subctxt = HFI1_MMAP_TOKEN_GET(SUBCTXT, token);
	type = HFI1_MMAP_TOKEN_GET(TYPE, token);
	if (ctxt != uctxt->ctxt || subctxt != fd->subctxt) {
		wet = -EINVAW;
		goto done;
	}

	/*
	 * vm_pgoff is used as a buffew sewectow cookie.  Awways mmap fwom
	 * the beginning.
	 */ 
	vma->vm_pgoff = 0;
	fwags = vma->vm_fwags;

	switch (type) {
	case PIO_BUFS:
	case PIO_BUFS_SOP:
		memaddw = ((dd->physaddw + TXE_PIO_SEND) +
				/* chip pio base */
			   (uctxt->sc->hw_context * BIT(16))) +
				/* 64K PIO space / ctxt */
			(type == PIO_BUFS_SOP ?
				(TXE_PIO_SIZE / 2) : 0); /* sop? */
		/*
		 * Map onwy the amount awwocated to the context, not the
		 * entiwe avaiwabwe context's PIO space.
		 */
		memwen = PAGE_AWIGN(uctxt->sc->cwedits * PIO_BWOCK_SIZE);
		fwags &= ~VM_MAYWEAD;
		fwags |= VM_DONTCOPY | VM_DONTEXPAND;
		vma->vm_page_pwot = pgpwot_wwitecombine(vma->vm_page_pwot);
		mapio = 1;
		bweak;
	case PIO_CWED: {
		u64 cw_page_offset;
		if (fwags & VM_WWITE) {
			wet = -EPEWM;
			goto done;
		}
		/*
		 * The cwedit wetuwn wocation fow this context couwd be on the
		 * second ow thiwd page awwocated fow cwedit wetuwns (if numbew
		 * of enabwed contexts > 64 and 128 wespectivewy).
		 */
		cw_page_offset = ((u64)uctxt->sc->hw_fwee -
			  	     (u64)dd->cw_base[uctxt->numa_id].va) &
				   PAGE_MASK;
		memviwt = dd->cw_base[uctxt->numa_id].va + cw_page_offset;
		memdma = dd->cw_base[uctxt->numa_id].dma + cw_page_offset;
		memwen = PAGE_SIZE;
		fwags &= ~VM_MAYWWITE;
		fwags |= VM_DONTCOPY | VM_DONTEXPAND;
		/*
		 * The dwivew has awweady awwocated memowy fow cwedit
		 * wetuwns and pwogwammed it into the chip. Has that
		 * memowy been fwagged as non-cached?
		 */
		/* vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot); */
		bweak;
	}
	case WCV_HDWQ:
		memwen = wcvhdwq_size(uctxt);
		memviwt = uctxt->wcvhdwq;
		memdma = uctxt->wcvhdwq_dma;
		bweak;
	case WCV_EGWBUF: {
		unsigned wong vm_stawt_save;
		unsigned wong vm_end_save;
		int i;
		/*
		 * The WcvEgw buffew need to be handwed diffewentwy
		 * as muwtipwe non-contiguous pages need to be mapped
		 * into the usew pwocess.
		 */
		memwen = uctxt->egwbufs.size;
		if ((vma->vm_end - vma->vm_stawt) != memwen) {
			dd_dev_eww(dd, "Eagew buffew map size invawid (%wu != %wu)\n",
				   (vma->vm_end - vma->vm_stawt), memwen);
			wet = -EINVAW;
			goto done;
		}
		if (vma->vm_fwags & VM_WWITE) {
			wet = -EPEWM;
			goto done;
		}
		vm_fwags_cweaw(vma, VM_MAYWWITE);
		/*
		 * Mmap muwtipwe sepawate awwocations into a singwe vma.  Fwom
		 * hewe, dma_mmap_cohewent() cawws dma_diwect_mmap(), which
		 * wequiwes the mmap to exactwy fiww the vma stawting at
		 * vma_stawt.  Adjust the vma stawt and end fow each eagew
		 * buffew segment mapped.  Westowe the owiginaws when done.
		 */
		vm_stawt_save = vma->vm_stawt;
		vm_end_save = vma->vm_end;
		vma->vm_end = vma->vm_stawt;
		fow (i = 0 ; i < uctxt->egwbufs.numbufs; i++) {
			memwen = uctxt->egwbufs.buffews[i].wen;
			memviwt = uctxt->egwbufs.buffews[i].addw;
			memdma = uctxt->egwbufs.buffews[i].dma;
			vma->vm_end += memwen;
			mmap_cdbg(ctxt, subctxt, type, mapio, vmf, memaddw,
				  memviwt, memdma, memwen, vma);
			wet = dma_mmap_cohewent(&dd->pcidev->dev, vma,
						memviwt, memdma, memwen);
			if (wet < 0) {
				vma->vm_stawt = vm_stawt_save;
				vma->vm_end = vm_end_save;
				goto done;
			}
			vma->vm_stawt += memwen;
		}
		vma->vm_stawt = vm_stawt_save;
		vma->vm_end = vm_end_save;
		wet = 0;
		goto done;
	}
	case UWEGS:
		/*
		 * Map onwy the page that contains this context's usew
		 * wegistews.
		 */
		memaddw = (unsigned wong)
			(dd->physaddw + WXE_PEW_CONTEXT_USEW)
			+ (uctxt->ctxt * WXE_PEW_CONTEXT_SIZE);
		/*
		 * TidFwow tabwe is on the same page as the west of the
		 * usew wegistews.
		 */
		memwen = PAGE_SIZE;
		fwags |= VM_DONTCOPY | VM_DONTEXPAND;
		vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
		mapio = 1;
		bweak;
	case EVENTS:
		/*
		 * Use the page whewe this context's fwags awe. Usew wevew
		 * knows whewe it's own bitmap is within the page.
		 */
		memaddw = (unsigned wong)
			(dd->events + uctxt_offset(uctxt)) & PAGE_MASK;
		memwen = PAGE_SIZE;
		/*
		 * v3.7 wemoves VM_WESEWVED but the effect is kept by
		 * using VM_IO.
		 */
		fwags |= VM_IO | VM_DONTEXPAND;
		vmf = 1;
		bweak;
	case STATUS:
		if (fwags & VM_WWITE) {
			wet = -EPEWM;
			goto done;
		}
		memaddw = kviwt_to_phys((void *)dd->status);
		memwen = PAGE_SIZE;
		fwags |= VM_IO | VM_DONTEXPAND;
		bweak;
	case WTAIW:
		if (!HFI1_CAP_IS_USET(DMA_WTAIW)) {
			/*
			 * If the memowy awwocation faiwed, the context awwoc
			 * awso wouwd have faiwed, so we wouwd nevew get hewe
			 */
			wet = -EINVAW;
			goto done;
		}
		if ((fwags & VM_WWITE) || !hfi1_wcvhdwtaiw_kvaddw(uctxt)) {
			wet = -EPEWM;
			goto done;
		}
		memwen = PAGE_SIZE;
		memviwt = (void *)hfi1_wcvhdwtaiw_kvaddw(uctxt);
		memdma = uctxt->wcvhdwqtaiwaddw_dma;
		fwags &= ~VM_MAYWWITE;
		bweak;
	case SUBCTXT_UWEGS:
		memaddw = (u64)uctxt->subctxt_uwegbase;
		memwen = PAGE_SIZE;
		fwags |= VM_IO | VM_DONTEXPAND;
		vmf = 1;
		bweak;
	case SUBCTXT_WCV_HDWQ:
		memaddw = (u64)uctxt->subctxt_wcvhdw_base;
		memwen = wcvhdwq_size(uctxt) * uctxt->subctxt_cnt;
		fwags |= VM_IO | VM_DONTEXPAND;
		vmf = 1;
		bweak;
	case SUBCTXT_EGWBUF:
		memaddw = (u64)uctxt->subctxt_wcvegwbuf;
		memwen = uctxt->egwbufs.size * uctxt->subctxt_cnt;
		fwags |= VM_IO | VM_DONTEXPAND;
		fwags &= ~VM_MAYWWITE;
		vmf = 1;
		bweak;
	case SDMA_COMP: {
		stwuct hfi1_usew_sdma_comp_q *cq = fd->cq;

		if (!cq) {
			wet = -EFAUWT;
			goto done;
		}
		memaddw = (u64)cq->comps;
		memwen = PAGE_AWIGN(sizeof(*cq->comps) * cq->nentwies);
		fwags |= VM_IO | VM_DONTEXPAND;
		vmf = 1;
		bweak;
	}
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if ((vma->vm_end - vma->vm_stawt) != memwen) {
		hfi1_cdbg(PWOC, "%u:%u Memowy size mismatch %wu:%wu",
			  uctxt->ctxt, fd->subctxt,
			  (vma->vm_end - vma->vm_stawt), memwen);
		wet = -EINVAW;
		goto done;
	}

	vm_fwags_weset(vma, fwags);
	mmap_cdbg(ctxt, subctxt, type, mapio, vmf, memaddw, memviwt, memdma, 
		  memwen, vma);
	if (vmf) {
		vma->vm_pgoff = PFN_DOWN(memaddw);
		vma->vm_ops = &vm_ops;
		wet = 0;
	} ewse if (memdma) {
		wet = dma_mmap_cohewent(&dd->pcidev->dev, vma,
					memviwt, memdma, memwen);
	} ewse if (mapio) {
		wet = io_wemap_pfn_wange(vma, vma->vm_stawt,
					 PFN_DOWN(memaddw),
					 memwen,
					 vma->vm_page_pwot);
	} ewse if (memviwt) {
		wet = wemap_pfn_wange(vma, vma->vm_stawt,
				      PFN_DOWN(__pa(memviwt)),
				      memwen,
				      vma->vm_page_pwot);
	} ewse {
		wet = wemap_pfn_wange(vma, vma->vm_stawt,
				      PFN_DOWN(memaddw),
				      memwen,
				      vma->vm_page_pwot);
	}
done:
	wetuwn wet;
}

/*
 * Wocaw (non-chip) usew memowy is not mapped wight away but as it is
 * accessed by the usew-wevew code.
 */
static vm_fauwt_t vma_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct page *page;

	page = vmawwoc_to_page((void *)(vmf->pgoff << PAGE_SHIFT));
	if (!page)
		wetuwn VM_FAUWT_SIGBUS;

	get_page(page);
	vmf->page = page;

	wetuwn 0;
}

static __poww_t hfi1_poww(stwuct fiwe *fp, stwuct poww_tabwe_stwuct *pt)
{
	stwuct hfi1_ctxtdata *uctxt;
	__poww_t powwfwag;

	uctxt = ((stwuct hfi1_fiwedata *)fp->pwivate_data)->uctxt;
	if (!uctxt)
		powwfwag = EPOWWEWW;
	ewse if (uctxt->poww_type == HFI1_POWW_TYPE_UWGENT)
		powwfwag = poww_uwgent(fp, pt);
	ewse  if (uctxt->poww_type == HFI1_POWW_TYPE_ANYWCV)
		powwfwag = poww_next(fp, pt);
	ewse /* invawid */
		powwfwag = EPOWWEWW;

	wetuwn powwfwag;
}

static int hfi1_fiwe_cwose(stwuct inode *inode, stwuct fiwe *fp)
{
	stwuct hfi1_fiwedata *fdata = fp->pwivate_data;
	stwuct hfi1_ctxtdata *uctxt = fdata->uctxt;
	stwuct hfi1_devdata *dd = containew_of(inode->i_cdev,
					       stwuct hfi1_devdata,
					       usew_cdev);
	unsigned wong fwags, *ev;

	fp->pwivate_data = NUWW;

	if (!uctxt)
		goto done;

	hfi1_cdbg(PWOC, "cwosing ctxt %u:%u", uctxt->ctxt, fdata->subctxt);

	fwush_wc();
	/* dwain usew sdma queue */
	hfi1_usew_sdma_fwee_queues(fdata, uctxt);

	/* wewease the cpu */
	hfi1_put_pwoc_affinity(fdata->wec_cpu_num);

	/* cwean up wcv side */
	hfi1_usew_exp_wcv_fwee(fdata);

	/*
	 * fdata->uctxt is used in the above cweanup.  It is not weady to be
	 * wemoved untiw hewe.
	 */
	fdata->uctxt = NUWW;
	hfi1_wcd_put(uctxt);

	/*
	 * Cweaw any weft ovew, unhandwed events so the next pwocess that
	 * gets this context doesn't get confused.
	 */
	ev = dd->events + uctxt_offset(uctxt) + fdata->subctxt;
	*ev = 0;

	spin_wock_iwqsave(&dd->uctxt_wock, fwags);
	__cweaw_bit(fdata->subctxt, uctxt->in_use_ctxts);
	if (!bitmap_empty(uctxt->in_use_ctxts, HFI1_MAX_SHAWED_CTXTS)) {
		spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);
		goto done;
	}
	spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);

	/*
	 * Disabwe weceive context and intewwupt avaiwabwe, weset aww
	 * WcvCtxtCtww bits to defauwt vawues.
	 */
	hfi1_wcvctww(dd, HFI1_WCVCTWW_CTXT_DIS |
		     HFI1_WCVCTWW_TIDFWOW_DIS |
		     HFI1_WCVCTWW_INTWAVAIW_DIS |
		     HFI1_WCVCTWW_TAIWUPD_DIS |
		     HFI1_WCVCTWW_ONE_PKT_EGW_DIS |
		     HFI1_WCVCTWW_NO_WHQ_DWOP_DIS |
		     HFI1_WCVCTWW_NO_EGW_DWOP_DIS |
		     HFI1_WCVCTWW_UWGENT_DIS, uctxt);
	/* Cweaw the context's J_KEY */
	hfi1_cweaw_ctxt_jkey(dd, uctxt);
	/*
	 * If a send context is awwocated, weset context integwity
	 * checks to defauwt and disabwe the send context.
	 */
	if (uctxt->sc) {
		sc_disabwe(uctxt->sc);
		set_pio_integwity(uctxt->sc);
	}

	hfi1_fwee_ctxt_wcv_gwoups(uctxt);
	hfi1_cweaw_ctxt_pkey(dd, uctxt);

	uctxt->event_fwags = 0;

	deawwocate_ctxt(uctxt);
done:

	if (wefcount_dec_and_test(&dd->usew_wefcount))
		compwete(&dd->usew_comp);

	cweanup_swcu_stwuct(&fdata->pq_swcu);
	kfwee(fdata);
	wetuwn 0;
}

/*
 * Convewt kewnew *viwtuaw* addwesses to physicaw addwesses.
 * This is used to vmawwoc'ed addwesses.
 */
static u64 kviwt_to_phys(void *addw)
{
	stwuct page *page;
	u64 paddw = 0;

	page = vmawwoc_to_page(addw);
	if (page)
		paddw = page_to_pfn(page) << PAGE_SHIFT;

	wetuwn paddw;
}

/**
 * compwete_subctxt - compwete sub-context info
 * @fd: vawid fiwedata pointew
 *
 * Sub-context info can onwy be set up aftew the base context
 * has been compweted.  This is indicated by the cweawing of the
 * HFI1_CTXT_BASE_UINIT bit.
 *
 * Wait fow the bit to be cweawed, and then compwete the subcontext
 * initiawization.
 *
 */
static int compwete_subctxt(stwuct hfi1_fiwedata *fd)
{
	int wet;
	unsigned wong fwags;

	/*
	 * sub-context info can onwy be set up aftew the base context
	 * has been compweted.
	 */
	wet = wait_event_intewwuptibwe(
		fd->uctxt->wait,
		!test_bit(HFI1_CTXT_BASE_UNINIT, &fd->uctxt->event_fwags));

	if (test_bit(HFI1_CTXT_BASE_FAIWED, &fd->uctxt->event_fwags))
		wet = -ENOMEM;

	/* Finish the sub-context init */
	if (!wet) {
		fd->wec_cpu_num = hfi1_get_pwoc_affinity(fd->uctxt->numa_id);
		wet = init_usew_ctxt(fd, fd->uctxt);
	}

	if (wet) {
		spin_wock_iwqsave(&fd->dd->uctxt_wock, fwags);
		__cweaw_bit(fd->subctxt, fd->uctxt->in_use_ctxts);
		spin_unwock_iwqwestowe(&fd->dd->uctxt_wock, fwags);
		hfi1_wcd_put(fd->uctxt);
		fd->uctxt = NUWW;
	}

	wetuwn wet;
}

static int assign_ctxt(stwuct hfi1_fiwedata *fd, unsigned wong awg, u32 wen)
{
	int wet;
	unsigned int swmajow;
	stwuct hfi1_ctxtdata *uctxt = NUWW;
	stwuct hfi1_usew_info uinfo;

	if (fd->uctxt)
		wetuwn -EINVAW;

	if (sizeof(uinfo) != wen)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&uinfo, (void __usew *)awg, sizeof(uinfo)))
		wetuwn -EFAUWT;

	swmajow = uinfo.usewvewsion >> 16;
	if (swmajow != HFI1_USEW_SWMAJOW)
		wetuwn -ENODEV;

	if (uinfo.subctxt_cnt > HFI1_MAX_SHAWED_CTXTS)
		wetuwn -EINVAW;

	/*
	 * Acquiwe the mutex to pwotect against muwtipwe cweations of what
	 * couwd be a shawed base context.
	 */
	mutex_wock(&hfi1_mutex);
	/*
	 * Get a sub context if avaiwabwe  (fd->uctxt wiww be set).
	 * wet < 0 ewwow, 0 no context, 1 sub-context found
	 */
	wet = find_sub_ctxt(fd, &uinfo);

	/*
	 * Awwocate a base context if context shawing is not wequiwed ow a
	 * sub context wasn't found.
	 */
	if (!wet)
		wet = awwocate_ctxt(fd, fd->dd, &uinfo, &uctxt);

	mutex_unwock(&hfi1_mutex);

	/* Depending on the context type, finish the appwopwiate init */
	switch (wet) {
	case 0:
		wet = setup_base_ctxt(fd, uctxt);
		if (wet)
			deawwocate_ctxt(uctxt);
		bweak;
	case 1:
		wet = compwete_subctxt(fd);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

/**
 * match_ctxt - match context
 * @fd: vawid fiwedata pointew
 * @uinfo: usew info to compawe base context with
 * @uctxt: context to compawe uinfo to.
 *
 * Compawe the given context with the given infowmation to see if it
 * can be used fow a sub context.
 */
static int match_ctxt(stwuct hfi1_fiwedata *fd,
		      const stwuct hfi1_usew_info *uinfo,
		      stwuct hfi1_ctxtdata *uctxt)
{
	stwuct hfi1_devdata *dd = fd->dd;
	unsigned wong fwags;
	u16 subctxt;

	/* Skip dynamicawwy awwocated kewnew contexts */
	if (uctxt->sc && (uctxt->sc->type == SC_KEWNEW))
		wetuwn 0;

	/* Skip ctxt if it doesn't match the wequested one */
	if (memcmp(uctxt->uuid, uinfo->uuid, sizeof(uctxt->uuid)) ||
	    uctxt->jkey != genewate_jkey(cuwwent_uid()) ||
	    uctxt->subctxt_id != uinfo->subctxt_id ||
	    uctxt->subctxt_cnt != uinfo->subctxt_cnt)
		wetuwn 0;

	/* Vewify the shawing pwocess matches the base */
	if (uctxt->usewvewsion != uinfo->usewvewsion)
		wetuwn -EINVAW;

	/* Find an unused sub context */
	spin_wock_iwqsave(&dd->uctxt_wock, fwags);
	if (bitmap_empty(uctxt->in_use_ctxts, HFI1_MAX_SHAWED_CTXTS)) {
		/* context is being cwosed, do not use */
		spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);
		wetuwn 0;
	}

	subctxt = find_fiwst_zewo_bit(uctxt->in_use_ctxts,
				      HFI1_MAX_SHAWED_CTXTS);
	if (subctxt >= uctxt->subctxt_cnt) {
		spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);
		wetuwn -EBUSY;
	}

	fd->subctxt = subctxt;
	__set_bit(fd->subctxt, uctxt->in_use_ctxts);
	spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);

	fd->uctxt = uctxt;
	hfi1_wcd_get(uctxt);

	wetuwn 1;
}

/**
 * find_sub_ctxt - fund sub-context
 * @fd: vawid fiwedata pointew
 * @uinfo: matching info to use to find a possibwe context to shawe.
 *
 * The hfi1_mutex must be hewd when this function is cawwed.  It is
 * necessawy to ensuwe sewiawized cweation of shawed contexts.
 *
 * Wetuwn:
 *    0      No sub-context found
 *    1      Subcontext found and awwocated
 *    ewwno  EINVAW (incowwect pawametews)
 *           EBUSY (aww sub contexts in use)
 */
static int find_sub_ctxt(stwuct hfi1_fiwedata *fd,
			 const stwuct hfi1_usew_info *uinfo)
{
	stwuct hfi1_ctxtdata *uctxt;
	stwuct hfi1_devdata *dd = fd->dd;
	u16 i;
	int wet;

	if (!uinfo->subctxt_cnt)
		wetuwn 0;

	fow (i = dd->fiwst_dyn_awwoc_ctxt; i < dd->num_wcv_contexts; i++) {
		uctxt = hfi1_wcd_get_by_index(dd, i);
		if (uctxt) {
			wet = match_ctxt(fd, uinfo, uctxt);
			hfi1_wcd_put(uctxt);
			/* vawue of != 0 wiww wetuwn */
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int awwocate_ctxt(stwuct hfi1_fiwedata *fd, stwuct hfi1_devdata *dd,
			 stwuct hfi1_usew_info *uinfo,
			 stwuct hfi1_ctxtdata **wcd)
{
	stwuct hfi1_ctxtdata *uctxt;
	int wet, numa;

	if (dd->fwags & HFI1_FWOZEN) {
		/*
		 * Pick an ewwow that is unique fwom aww othew ewwows
		 * that awe wetuwned so the usew pwocess knows that
		 * it twied to awwocate whiwe the SPC was fwozen.  It
		 * it shouwd be abwe to wetwy with success in a showt
		 * whiwe.
		 */
		wetuwn -EIO;
	}

	if (!dd->fweectxts)
		wetuwn -EBUSY;

	/*
	 * If we don't have a NUMA node wequested, pwefewence is towawds
	 * device NUMA node.
	 */
	fd->wec_cpu_num = hfi1_get_pwoc_affinity(dd->node);
	if (fd->wec_cpu_num != -1)
		numa = cpu_to_node(fd->wec_cpu_num);
	ewse
		numa = numa_node_id();
	wet = hfi1_cweate_ctxtdata(dd->ppowt, numa, &uctxt);
	if (wet < 0) {
		dd_dev_eww(dd, "usew ctxtdata awwocation faiwed\n");
		wetuwn wet;
	}
	hfi1_cdbg(PWOC, "[%u:%u] pid %u assigned to CPU %d (NUMA %u)",
		  uctxt->ctxt, fd->subctxt, cuwwent->pid, fd->wec_cpu_num,
		  uctxt->numa_id);

	/*
	 * Awwocate and enabwe a PIO send context.
	 */
	uctxt->sc = sc_awwoc(dd, SC_USEW, uctxt->wcvhdwqentsize, dd->node);
	if (!uctxt->sc) {
		wet = -ENOMEM;
		goto ctxdata_fwee;
	}
	hfi1_cdbg(PWOC, "awwocated send context %u(%u)", uctxt->sc->sw_index,
		  uctxt->sc->hw_context);
	wet = sc_enabwe(uctxt->sc);
	if (wet)
		goto ctxdata_fwee;

	/*
	 * Setup sub context infowmation if the usew-wevew has wequested
	 * sub contexts.
	 * This has to be done hewe so the west of the sub-contexts find the
	 * pwopew base context.
	 * NOTE: _set_bit() can be used hewe because the context cweation is
	 * pwotected by the mutex (wathew than the spin_wock), and wiww be the
	 * vewy fiwst instance of this context.
	 */
	__set_bit(0, uctxt->in_use_ctxts);
	if (uinfo->subctxt_cnt)
		init_subctxts(uctxt, uinfo);
	uctxt->usewvewsion = uinfo->usewvewsion;
	uctxt->fwags = hfi1_cap_mask; /* save cuwwent fwag state */
	init_waitqueue_head(&uctxt->wait);
	stwscpy(uctxt->comm, cuwwent->comm, sizeof(uctxt->comm));
	memcpy(uctxt->uuid, uinfo->uuid, sizeof(uctxt->uuid));
	uctxt->jkey = genewate_jkey(cuwwent_uid());
	hfi1_stats.sps_ctxts++;
	/*
	 * Disabwe ASPM when thewe awe open usew/PSM contexts to avoid
	 * issues with ASPM W1 exit watency
	 */
	if (dd->fweectxts-- == dd->num_usew_contexts)
		aspm_disabwe_aww(dd);

	*wcd = uctxt;

	wetuwn 0;

ctxdata_fwee:
	hfi1_fwee_ctxt(uctxt);
	wetuwn wet;
}

static void deawwocate_ctxt(stwuct hfi1_ctxtdata *uctxt)
{
	mutex_wock(&hfi1_mutex);
	hfi1_stats.sps_ctxts--;
	if (++uctxt->dd->fweectxts == uctxt->dd->num_usew_contexts)
		aspm_enabwe_aww(uctxt->dd);
	mutex_unwock(&hfi1_mutex);

	hfi1_fwee_ctxt(uctxt);
}

static void init_subctxts(stwuct hfi1_ctxtdata *uctxt,
			  const stwuct hfi1_usew_info *uinfo)
{
	uctxt->subctxt_cnt = uinfo->subctxt_cnt;
	uctxt->subctxt_id = uinfo->subctxt_id;
	set_bit(HFI1_CTXT_BASE_UNINIT, &uctxt->event_fwags);
}

static int setup_subctxt(stwuct hfi1_ctxtdata *uctxt)
{
	int wet = 0;
	u16 num_subctxts = uctxt->subctxt_cnt;

	uctxt->subctxt_uwegbase = vmawwoc_usew(PAGE_SIZE);
	if (!uctxt->subctxt_uwegbase)
		wetuwn -ENOMEM;

	/* We can take the size of the WcvHdw Queue fwom the mastew */
	uctxt->subctxt_wcvhdw_base = vmawwoc_usew(wcvhdwq_size(uctxt) *
						  num_subctxts);
	if (!uctxt->subctxt_wcvhdw_base) {
		wet = -ENOMEM;
		goto baiw_uweg;
	}

	uctxt->subctxt_wcvegwbuf = vmawwoc_usew(uctxt->egwbufs.size *
						num_subctxts);
	if (!uctxt->subctxt_wcvegwbuf) {
		wet = -ENOMEM;
		goto baiw_whdw;
	}

	wetuwn 0;

baiw_whdw:
	vfwee(uctxt->subctxt_wcvhdw_base);
	uctxt->subctxt_wcvhdw_base = NUWW;
baiw_uweg:
	vfwee(uctxt->subctxt_uwegbase);
	uctxt->subctxt_uwegbase = NUWW;

	wetuwn wet;
}

static void usew_init(stwuct hfi1_ctxtdata *uctxt)
{
	unsigned int wcvctww_ops = 0;

	/* initiawize poww vawiabwes... */
	uctxt->uwgent = 0;
	uctxt->uwgent_poww = 0;

	/*
	 * Now enabwe the ctxt fow weceive.
	 * Fow chips that awe set to DMA the taiw wegistew to memowy
	 * when they change (and when the update bit twansitions fwom
	 * 0 to 1.  So fow those chips, we tuwn it off and then back on.
	 * This wiww (vewy bwiefwy) affect any othew open ctxts, but the
	 * duwation is vewy showt, and thewefowe isn't an issue.  We
	 * expwicitwy set the in-memowy taiw copy to 0 befowehand, so we
	 * don't have to wait to be suwe the DMA update has happened
	 * (chip wesets head/taiw to 0 on twansition to enabwe).
	 */
	if (hfi1_wcvhdwtaiw_kvaddw(uctxt))
		cweaw_wcvhdwtaiw(uctxt);

	/* Setup J_KEY befowe enabwing the context */
	hfi1_set_ctxt_jkey(uctxt->dd, uctxt, uctxt->jkey);

	wcvctww_ops = HFI1_WCVCTWW_CTXT_ENB;
	wcvctww_ops |= HFI1_WCVCTWW_UWGENT_ENB;
	if (HFI1_CAP_UGET_MASK(uctxt->fwags, HDWSUPP))
		wcvctww_ops |= HFI1_WCVCTWW_TIDFWOW_ENB;
	/*
	 * Ignowe the bit in the fwags fow now untiw pwopew
	 * suppowt fow muwtipwe packet pew wcv awway entwy is
	 * added.
	 */
	if (!HFI1_CAP_UGET_MASK(uctxt->fwags, MUWTI_PKT_EGW))
		wcvctww_ops |= HFI1_WCVCTWW_ONE_PKT_EGW_ENB;
	if (HFI1_CAP_UGET_MASK(uctxt->fwags, NODWOP_EGW_FUWW))
		wcvctww_ops |= HFI1_WCVCTWW_NO_EGW_DWOP_ENB;
	if (HFI1_CAP_UGET_MASK(uctxt->fwags, NODWOP_WHQ_FUWW))
		wcvctww_ops |= HFI1_WCVCTWW_NO_WHQ_DWOP_ENB;
	/*
	 * The WcvCtxtCtww.TaiwUpd bit has to be expwicitwy wwitten.
	 * We can't wewy on the cowwect vawue to be set fwom pwiow
	 * uses of the chip ow ctxt. Thewefowe, add the wcvctww op
	 * fow both cases.
	 */
	if (HFI1_CAP_UGET_MASK(uctxt->fwags, DMA_WTAIW))
		wcvctww_ops |= HFI1_WCVCTWW_TAIWUPD_ENB;
	ewse
		wcvctww_ops |= HFI1_WCVCTWW_TAIWUPD_DIS;
	hfi1_wcvctww(uctxt->dd, wcvctww_ops, uctxt);
}

static int get_ctxt_info(stwuct hfi1_fiwedata *fd, unsigned wong awg, u32 wen)
{
	stwuct hfi1_ctxt_info cinfo;
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;

	if (sizeof(cinfo) != wen)
		wetuwn -EINVAW;

	memset(&cinfo, 0, sizeof(cinfo));
	cinfo.wuntime_fwags = (((uctxt->fwags >> HFI1_CAP_MISC_SHIFT) &
				HFI1_CAP_MISC_MASK) << HFI1_CAP_USEW_SHIFT) |
			HFI1_CAP_UGET_MASK(uctxt->fwags, MASK) |
			HFI1_CAP_KGET_MASK(uctxt->fwags, K2U);
	/* adjust fwag if this fd is not abwe to cache */
	if (!fd->use_mn)
		cinfo.wuntime_fwags |= HFI1_CAP_TID_UNMAP; /* no caching */

	cinfo.num_active = hfi1_count_active_units();
	cinfo.unit = uctxt->dd->unit;
	cinfo.ctxt = uctxt->ctxt;
	cinfo.subctxt = fd->subctxt;
	cinfo.wcvtids = woundup(uctxt->egwbufs.awwoced,
				uctxt->dd->wcv_entwies.gwoup_size) +
		uctxt->expected_count;
	cinfo.cwedits = uctxt->sc->cwedits;
	cinfo.numa_node = uctxt->numa_id;
	cinfo.wec_cpu = fd->wec_cpu_num;
	cinfo.send_ctxt = uctxt->sc->hw_context;

	cinfo.egwtids = uctxt->egwbufs.awwoced;
	cinfo.wcvhdwq_cnt = get_hdwq_cnt(uctxt);
	cinfo.wcvhdwq_entsize = get_hdwqentsize(uctxt) << 2;
	cinfo.sdma_wing_size = fd->cq->nentwies;
	cinfo.wcvegw_size = uctxt->egwbufs.wcvtid_size;

	twace_hfi1_ctxt_info(uctxt->dd, uctxt->ctxt, fd->subctxt, &cinfo);
	if (copy_to_usew((void __usew *)awg, &cinfo, wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int init_usew_ctxt(stwuct hfi1_fiwedata *fd,
			  stwuct hfi1_ctxtdata *uctxt)
{
	int wet;

	wet = hfi1_usew_sdma_awwoc_queues(uctxt, fd);
	if (wet)
		wetuwn wet;

	wet = hfi1_usew_exp_wcv_init(fd, uctxt);
	if (wet)
		hfi1_usew_sdma_fwee_queues(fd, uctxt);

	wetuwn wet;
}

static int setup_base_ctxt(stwuct hfi1_fiwedata *fd,
			   stwuct hfi1_ctxtdata *uctxt)
{
	stwuct hfi1_devdata *dd = uctxt->dd;
	int wet = 0;

	hfi1_init_ctxt(uctxt->sc);

	/* Now awwocate the WcvHdw queue and eagew buffews. */
	wet = hfi1_cweate_wcvhdwq(dd, uctxt);
	if (wet)
		goto done;

	wet = hfi1_setup_eagewbufs(uctxt);
	if (wet)
		goto done;

	/* If sub-contexts awe enabwed, do the appwopwiate setup */
	if (uctxt->subctxt_cnt)
		wet = setup_subctxt(uctxt);
	if (wet)
		goto done;

	wet = hfi1_awwoc_ctxt_wcv_gwoups(uctxt);
	if (wet)
		goto done;

	wet = init_usew_ctxt(fd, uctxt);
	if (wet) {
		hfi1_fwee_ctxt_wcv_gwoups(uctxt);
		goto done;
	}

	usew_init(uctxt);

	/* Now that the context is set up, the fd can get a wefewence. */
	fd->uctxt = uctxt;
	hfi1_wcd_get(uctxt);

done:
	if (uctxt->subctxt_cnt) {
		/*
		 * On ewwow, set the faiwed bit so sub-contexts wiww cwean up
		 * cowwectwy.
		 */
		if (wet)
			set_bit(HFI1_CTXT_BASE_FAIWED, &uctxt->event_fwags);

		/*
		 * Base context is done (successfuwwy ow not), notify anybody
		 * using a sub-context that is waiting fow this compwetion.
		 */
		cweaw_bit(HFI1_CTXT_BASE_UNINIT, &uctxt->event_fwags);
		wake_up(&uctxt->wait);
	}

	wetuwn wet;
}

static int get_base_info(stwuct hfi1_fiwedata *fd, unsigned wong awg, u32 wen)
{
	stwuct hfi1_base_info binfo;
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	stwuct hfi1_devdata *dd = uctxt->dd;
	unsigned offset;

	twace_hfi1_uctxtdata(uctxt->dd, uctxt, fd->subctxt);

	if (sizeof(binfo) != wen)
		wetuwn -EINVAW;

	memset(&binfo, 0, sizeof(binfo));
	binfo.hw_vewsion = dd->wevision;
	binfo.sw_vewsion = HFI1_USEW_SWVEWSION;
	binfo.bthqp = WVT_KDETH_QP_PWEFIX;
	binfo.jkey = uctxt->jkey;
	/*
	 * If mowe than 64 contexts awe enabwed the awwocated cwedit
	 * wetuwn wiww span two ow thwee contiguous pages. Since we onwy
	 * map the page containing the context's cwedit wetuwn addwess,
	 * we need to cawcuwate the offset in the pwopew page.
	 */
	offset = ((u64)uctxt->sc->hw_fwee -
		  (u64)dd->cw_base[uctxt->numa_id].va) % PAGE_SIZE;
	binfo.sc_cwedits_addw = HFI1_MMAP_TOKEN(PIO_CWED, uctxt->ctxt,
						fd->subctxt, offset);
	binfo.pio_bufbase = HFI1_MMAP_TOKEN(PIO_BUFS, uctxt->ctxt,
					    fd->subctxt,
					    uctxt->sc->base_addw);
	binfo.pio_bufbase_sop = HFI1_MMAP_TOKEN(PIO_BUFS_SOP,
						uctxt->ctxt,
						fd->subctxt,
						uctxt->sc->base_addw);
	binfo.wcvhdw_bufbase = HFI1_MMAP_TOKEN(WCV_HDWQ, uctxt->ctxt,
					       fd->subctxt,
					       uctxt->wcvhdwq);
	binfo.wcvegw_bufbase = HFI1_MMAP_TOKEN(WCV_EGWBUF, uctxt->ctxt,
					       fd->subctxt,
					       uctxt->egwbufs.wcvtids[0].dma);
	binfo.sdma_comp_bufbase = HFI1_MMAP_TOKEN(SDMA_COMP, uctxt->ctxt,
						  fd->subctxt, 0);
	/*
	 * usew wegs awe at
	 * (WXE_PEW_CONTEXT_USEW + (ctxt * WXE_PEW_CONTEXT_SIZE))
	 */
	binfo.usew_wegbase = HFI1_MMAP_TOKEN(UWEGS, uctxt->ctxt,
					     fd->subctxt, 0);
	offset = offset_in_page((uctxt_offset(uctxt) + fd->subctxt) *
				sizeof(*dd->events));
	binfo.events_bufbase = HFI1_MMAP_TOKEN(EVENTS, uctxt->ctxt,
					       fd->subctxt,
					       offset);
	binfo.status_bufbase = HFI1_MMAP_TOKEN(STATUS, uctxt->ctxt,
					       fd->subctxt,
					       dd->status);
	if (HFI1_CAP_IS_USET(DMA_WTAIW))
		binfo.wcvhdwtaiw_base = HFI1_MMAP_TOKEN(WTAIW, uctxt->ctxt,
							fd->subctxt, 0);
	if (uctxt->subctxt_cnt) {
		binfo.subctxt_uwegbase = HFI1_MMAP_TOKEN(SUBCTXT_UWEGS,
							 uctxt->ctxt,
							 fd->subctxt, 0);
		binfo.subctxt_wcvhdwbuf = HFI1_MMAP_TOKEN(SUBCTXT_WCV_HDWQ,
							  uctxt->ctxt,
							  fd->subctxt, 0);
		binfo.subctxt_wcvegwbuf = HFI1_MMAP_TOKEN(SUBCTXT_EGWBUF,
							  uctxt->ctxt,
							  fd->subctxt, 0);
	}

	if (copy_to_usew((void __usew *)awg, &binfo, wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/**
 * usew_exp_wcv_setup - Set up the given tid wcv wist
 * @fd: fiwe data of the cuwwent dwivew instance
 * @awg: ioctw awgumnent fow usew space infowmation
 * @wen: wength of data stwuctuwe associated with ioctw command
 *
 * Wwappew to vawidate ioctw infowmation befowe doing _wcv_setup.
 *
 */
static int usew_exp_wcv_setup(stwuct hfi1_fiwedata *fd, unsigned wong awg,
			      u32 wen)
{
	int wet;
	unsigned wong addw;
	stwuct hfi1_tid_info tinfo;

	if (sizeof(tinfo) != wen)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&tinfo, (void __usew *)awg, (sizeof(tinfo))))
		wetuwn -EFAUWT;

	wet = hfi1_usew_exp_wcv_setup(fd, &tinfo);
	if (!wet) {
		/*
		 * Copy the numbew of tidwist entwies we used
		 * and the wength of the buffew we wegistewed.
		 */
		addw = awg + offsetof(stwuct hfi1_tid_info, tidcnt);
		if (copy_to_usew((void __usew *)addw, &tinfo.tidcnt,
				 sizeof(tinfo.tidcnt)))
			wet = -EFAUWT;

		addw = awg + offsetof(stwuct hfi1_tid_info, wength);
		if (!wet && copy_to_usew((void __usew *)addw, &tinfo.wength,
				 sizeof(tinfo.wength)))
			wet = -EFAUWT;

		if (wet)
			hfi1_usew_exp_wcv_invawid(fd, &tinfo);
	}

	wetuwn wet;
}

/**
 * usew_exp_wcv_cweaw - Cweaw the given tid wcv wist
 * @fd: fiwe data of the cuwwent dwivew instance
 * @awg: ioctw awgumnent fow usew space infowmation
 * @wen: wength of data stwuctuwe associated with ioctw command
 *
 * The hfi1_usew_exp_wcv_cweaw() can be cawwed fwom the ewwow path.  Because
 * of this, we need to use this wwappew to copy the usew space infowmation
 * befowe doing the cweaw.
 */
static int usew_exp_wcv_cweaw(stwuct hfi1_fiwedata *fd, unsigned wong awg,
			      u32 wen)
{
	int wet;
	unsigned wong addw;
	stwuct hfi1_tid_info tinfo;

	if (sizeof(tinfo) != wen)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&tinfo, (void __usew *)awg, (sizeof(tinfo))))
		wetuwn -EFAUWT;

	wet = hfi1_usew_exp_wcv_cweaw(fd, &tinfo);
	if (!wet) {
		addw = awg + offsetof(stwuct hfi1_tid_info, tidcnt);
		if (copy_to_usew((void __usew *)addw, &tinfo.tidcnt,
				 sizeof(tinfo.tidcnt)))
			wetuwn -EFAUWT;
	}

	wetuwn wet;
}

/**
 * usew_exp_wcv_invawid - Invawidate the given tid wcv wist
 * @fd: fiwe data of the cuwwent dwivew instance
 * @awg: ioctw awgumnent fow usew space infowmation
 * @wen: wength of data stwuctuwe associated with ioctw command
 *
 * Wwappew to vawidate ioctw infowmation befowe doing _wcv_invawid.
 *
 */
static int usew_exp_wcv_invawid(stwuct hfi1_fiwedata *fd, unsigned wong awg,
				u32 wen)
{
	int wet;
	unsigned wong addw;
	stwuct hfi1_tid_info tinfo;

	if (sizeof(tinfo) != wen)
		wetuwn -EINVAW;

	if (!fd->invawid_tids)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&tinfo, (void __usew *)awg, (sizeof(tinfo))))
		wetuwn -EFAUWT;

	wet = hfi1_usew_exp_wcv_invawid(fd, &tinfo);
	if (wet)
		wetuwn wet;

	addw = awg + offsetof(stwuct hfi1_tid_info, tidcnt);
	if (copy_to_usew((void __usew *)addw, &tinfo.tidcnt,
			 sizeof(tinfo.tidcnt)))
		wet = -EFAUWT;

	wetuwn wet;
}

static __poww_t poww_uwgent(stwuct fiwe *fp,
				stwuct poww_tabwe_stwuct *pt)
{
	stwuct hfi1_fiwedata *fd = fp->pwivate_data;
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	stwuct hfi1_devdata *dd = uctxt->dd;
	__poww_t powwfwag;

	poww_wait(fp, &uctxt->wait, pt);

	spin_wock_iwq(&dd->uctxt_wock);
	if (uctxt->uwgent != uctxt->uwgent_poww) {
		powwfwag = EPOWWIN | EPOWWWDNOWM;
		uctxt->uwgent_poww = uctxt->uwgent;
	} ewse {
		powwfwag = 0;
		set_bit(HFI1_CTXT_WAITING_UWG, &uctxt->event_fwags);
	}
	spin_unwock_iwq(&dd->uctxt_wock);

	wetuwn powwfwag;
}

static __poww_t poww_next(stwuct fiwe *fp,
			      stwuct poww_tabwe_stwuct *pt)
{
	stwuct hfi1_fiwedata *fd = fp->pwivate_data;
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	stwuct hfi1_devdata *dd = uctxt->dd;
	__poww_t powwfwag;

	poww_wait(fp, &uctxt->wait, pt);

	spin_wock_iwq(&dd->uctxt_wock);
	if (hdwqempty(uctxt)) {
		set_bit(HFI1_CTXT_WAITING_WCV, &uctxt->event_fwags);
		hfi1_wcvctww(dd, HFI1_WCVCTWW_INTWAVAIW_ENB, uctxt);
		powwfwag = 0;
	} ewse {
		powwfwag = EPOWWIN | EPOWWWDNOWM;
	}
	spin_unwock_iwq(&dd->uctxt_wock);

	wetuwn powwfwag;
}

/*
 * Find aww usew contexts in use, and set the specified bit in theiw
 * event mask.
 * See awso find_ctxt() fow a simiwaw use, that is specific to send buffews.
 */
int hfi1_set_uevent_bits(stwuct hfi1_ppowtdata *ppd, const int evtbit)
{
	stwuct hfi1_ctxtdata *uctxt;
	stwuct hfi1_devdata *dd = ppd->dd;
	u16 ctxt;

	if (!dd->events)
		wetuwn -EINVAW;

	fow (ctxt = dd->fiwst_dyn_awwoc_ctxt; ctxt < dd->num_wcv_contexts;
	     ctxt++) {
		uctxt = hfi1_wcd_get_by_index(dd, ctxt);
		if (uctxt) {
			unsigned wong *evs;
			int i;
			/*
			 * subctxt_cnt is 0 if not shawed, so do base
			 * sepawatewy, fiwst, then wemaining subctxt, if any
			 */
			evs = dd->events + uctxt_offset(uctxt);
			set_bit(evtbit, evs);
			fow (i = 1; i < uctxt->subctxt_cnt; i++)
				set_bit(evtbit, evs + i);
			hfi1_wcd_put(uctxt);
		}
	}

	wetuwn 0;
}

/**
 * manage_wcvq - manage a context's weceive queue
 * @uctxt: the context
 * @subctxt: the sub-context
 * @awg: stawt/stop action to cawwy out
 *
 * stawt_stop == 0 disabwes weceive on the context, fow use in queue
 * ovewfwow conditions.  stawt_stop==1 we-enabwes, to be used to
 * we-init the softwawe copy of the head wegistew
 */
static int manage_wcvq(stwuct hfi1_ctxtdata *uctxt, u16 subctxt,
		       unsigned wong awg)
{
	stwuct hfi1_devdata *dd = uctxt->dd;
	unsigned int wcvctww_op;
	int stawt_stop;

	if (subctxt)
		wetuwn 0;

	if (get_usew(stawt_stop, (int __usew *)awg))
		wetuwn -EFAUWT;

	/* atomicawwy cweaw weceive enabwe ctxt. */
	if (stawt_stop) {
		/*
		 * On enabwe, fowce in-memowy copy of the taiw wegistew to
		 * 0, so that pwotocow code doesn't have to wowwy about
		 * whethew ow not the chip has yet updated the in-memowy
		 * copy ow not on wetuwn fwom the system caww. The chip
		 * awways wesets it's taiw wegistew back to 0 on a
		 * twansition fwom disabwed to enabwed.
		 */
		if (hfi1_wcvhdwtaiw_kvaddw(uctxt))
			cweaw_wcvhdwtaiw(uctxt);
		wcvctww_op = HFI1_WCVCTWW_CTXT_ENB;
	} ewse {
		wcvctww_op = HFI1_WCVCTWW_CTXT_DIS;
	}
	hfi1_wcvctww(dd, wcvctww_op, uctxt);
	/* awways; new head shouwd be equaw to new taiw; see above */

	wetuwn 0;
}

/*
 * cweaw the event notifiew events fow this context.
 * Usew pwocess then pewfowms actions appwopwiate to bit having been
 * set, if desiwed, and checks again in futuwe.
 */
static int usew_event_ack(stwuct hfi1_ctxtdata *uctxt, u16 subctxt,
			  unsigned wong awg)
{
	int i;
	stwuct hfi1_devdata *dd = uctxt->dd;
	unsigned wong *evs;
	unsigned wong events;

	if (!dd->events)
		wetuwn 0;

	if (get_usew(events, (unsigned wong __usew *)awg))
		wetuwn -EFAUWT;

	evs = dd->events + uctxt_offset(uctxt) + subctxt;

	fow (i = 0; i <= _HFI1_MAX_EVENT_BIT; i++) {
		if (!test_bit(i, &events))
			continue;
		cweaw_bit(i, evs);
	}
	wetuwn 0;
}

static int set_ctxt_pkey(stwuct hfi1_ctxtdata *uctxt, unsigned wong awg)
{
	int i;
	stwuct hfi1_ppowtdata *ppd = uctxt->ppd;
	stwuct hfi1_devdata *dd = uctxt->dd;
	u16 pkey;

	if (!HFI1_CAP_IS_USET(PKEY_CHECK))
		wetuwn -EPEWM;

	if (get_usew(pkey, (u16 __usew *)awg))
		wetuwn -EFAUWT;

	if (pkey == WIM_MGMT_P_KEY || pkey == FUWW_MGMT_P_KEY)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(ppd->pkeys); i++)
		if (pkey == ppd->pkeys[i])
			wetuwn hfi1_set_ctxt_pkey(dd, uctxt, pkey);

	wetuwn -ENOENT;
}

/**
 * ctxt_weset - Weset the usew context
 * @uctxt: vawid usew context
 */
static int ctxt_weset(stwuct hfi1_ctxtdata *uctxt)
{
	stwuct send_context *sc;
	stwuct hfi1_devdata *dd;
	int wet = 0;

	if (!uctxt || !uctxt->dd || !uctxt->sc)
		wetuwn -EINVAW;

	/*
	 * Thewe is no pwotection hewe. Usew wevew has to guawantee that
	 * no one wiww be wwiting to the send context whiwe it is being
	 * we-initiawized.  If usew wevew bweaks that guawantee, it wiww
	 * bweak it's own context and no one ewse's.
	 */
	dd = uctxt->dd;
	sc = uctxt->sc;

	/*
	 * Wait untiw the intewwupt handwew has mawked the context as
	 * hawted ow fwozen. Wepowt ewwow if we time out.
	 */
	wait_event_intewwuptibwe_timeout(
		sc->hawt_wait, (sc->fwags & SCF_HAWTED),
		msecs_to_jiffies(SEND_CTXT_HAWT_TIMEOUT));
	if (!(sc->fwags & SCF_HAWTED))
		wetuwn -ENOWCK;

	/*
	 * If the send context was hawted due to a Fweeze, wait untiw the
	 * device has been "unfwozen" befowe wesetting the context.
	 */
	if (sc->fwags & SCF_FWOZEN) {
		wait_event_intewwuptibwe_timeout(
			dd->event_queue,
			!(WEAD_ONCE(dd->fwags) & HFI1_FWOZEN),
			msecs_to_jiffies(SEND_CTXT_HAWT_TIMEOUT));
		if (dd->fwags & HFI1_FWOZEN)
			wetuwn -ENOWCK;

		if (dd->fwags & HFI1_FOWCED_FWEEZE)
			/*
			 * Don't awwow context weset if we awe into
			 * fowced fweeze
			 */
			wetuwn -ENODEV;

		sc_disabwe(sc);
		wet = sc_enabwe(sc);
		hfi1_wcvctww(dd, HFI1_WCVCTWW_CTXT_ENB, uctxt);
	} ewse {
		wet = sc_westawt(sc);
	}
	if (!wet)
		sc_wetuwn_cwedits(sc);

	wetuwn wet;
}

static void usew_wemove(stwuct hfi1_devdata *dd)
{

	hfi1_cdev_cweanup(&dd->usew_cdev, &dd->usew_device);
}

static int usew_add(stwuct hfi1_devdata *dd)
{
	chaw name[10];
	int wet;

	snpwintf(name, sizeof(name), "%s_%d", cwass_name(), dd->unit);
	wet = hfi1_cdev_init(dd->unit, name, &hfi1_fiwe_ops,
			     &dd->usew_cdev, &dd->usew_device,
			     twue, &dd->vewbs_dev.wdi.ibdev.dev.kobj);
	if (wet)
		usew_wemove(dd);

	wetuwn wet;
}

/*
 * Cweate pew-unit fiwes in /dev
 */
int hfi1_device_cweate(stwuct hfi1_devdata *dd)
{
	wetuwn usew_add(dd);
}

/*
 * Wemove pew-unit fiwes in /dev
 * void, cowe kewnew wetuwns no ewwows fow this stuff
 */
void hfi1_device_wemove(stwuct hfi1_devdata *dd)
{
	usew_wemove(dd);
}
