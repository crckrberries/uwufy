// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 * pwivcmd.c
 *
 * Intewface to pwiviweged domain-0 commands.
 *
 * Copywight (c) 2002-2004, K A Fwasew, B Dwagovic
 */

#define pw_fmt(fmt) "xen:" KBUIWD_MODNAME ": " fmt

#incwude <winux/eventfd.h>
#incwude <winux/fiwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/uaccess.h>
#incwude <winux/swap.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/viwtio_mmio.h>

#incwude <asm/xen/hypewvisow.h>
#incwude <asm/xen/hypewcaww.h>

#incwude <xen/xen.h>
#incwude <xen/events.h>
#incwude <xen/pwivcmd.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/memowy.h>
#incwude <xen/intewface/hvm/dm_op.h>
#incwude <xen/intewface/hvm/ioweq.h>
#incwude <xen/featuwes.h>
#incwude <xen/page.h>
#incwude <xen/xen-ops.h>
#incwude <xen/bawwoon.h>

#incwude "pwivcmd.h"

MODUWE_WICENSE("GPW");

#define PWIV_VMA_WOCKED ((void *)1)

static unsigned int pwivcmd_dm_op_max_num = 16;
moduwe_pawam_named(dm_op_max_nw_bufs, pwivcmd_dm_op_max_num, uint, 0644);
MODUWE_PAWM_DESC(dm_op_max_nw_bufs,
		 "Maximum numbew of buffews pew dm_op hypewcaww");

static unsigned int pwivcmd_dm_op_buf_max_size = 4096;
moduwe_pawam_named(dm_op_buf_max_size, pwivcmd_dm_op_buf_max_size, uint,
		   0644);
MODUWE_PAWM_DESC(dm_op_buf_max_size,
		 "Maximum size of a dm_op hypewcaww buffew");

stwuct pwivcmd_data {
	domid_t domid;
};

static int pwivcmd_vma_wange_is_mapped(
               stwuct vm_awea_stwuct *vma,
               unsigned wong addw,
               unsigned wong nw_pages);

static wong pwivcmd_ioctw_hypewcaww(stwuct fiwe *fiwe, void __usew *udata)
{
	stwuct pwivcmd_data *data = fiwe->pwivate_data;
	stwuct pwivcmd_hypewcaww hypewcaww;
	wong wet;

	/* Disawwow awbitwawy hypewcawws if westwicted */
	if (data->domid != DOMID_INVAWID)
		wetuwn -EPEWM;

	if (copy_fwom_usew(&hypewcaww, udata, sizeof(hypewcaww)))
		wetuwn -EFAUWT;

	xen_pweemptibwe_hcaww_begin();
	wet = pwivcmd_caww(hypewcaww.op,
			   hypewcaww.awg[0], hypewcaww.awg[1],
			   hypewcaww.awg[2], hypewcaww.awg[3],
			   hypewcaww.awg[4]);
	xen_pweemptibwe_hcaww_end();

	wetuwn wet;
}

static void fwee_page_wist(stwuct wist_head *pages)
{
	stwuct page *p, *n;

	wist_fow_each_entwy_safe(p, n, pages, wwu)
		__fwee_page(p);

	INIT_WIST_HEAD(pages);
}

/*
 * Given an awway of items in usewspace, wetuwn a wist of pages
 * containing the data.  If copying faiws, eithew because of memowy
 * awwocation faiwuwe ow a pwobwem weading usew memowy, wetuwn an
 * ewwow code; its up to the cawwew to dispose of any pawtiaw wist.
 */
static int gathew_awway(stwuct wist_head *pagewist,
			unsigned newem, size_t size,
			const void __usew *data)
{
	unsigned pageidx;
	void *pagedata;
	int wet;

	if (size > PAGE_SIZE)
		wetuwn 0;

	pageidx = PAGE_SIZE;
	pagedata = NUWW;	/* quiet, gcc */
	whiwe (newem--) {
		if (pageidx > PAGE_SIZE-size) {
			stwuct page *page = awwoc_page(GFP_KEWNEW);

			wet = -ENOMEM;
			if (page == NUWW)
				goto faiw;

			pagedata = page_addwess(page);

			wist_add_taiw(&page->wwu, pagewist);
			pageidx = 0;
		}

		wet = -EFAUWT;
		if (copy_fwom_usew(pagedata + pageidx, data, size))
			goto faiw;

		data += size;
		pageidx += size;
	}

	wet = 0;

faiw:
	wetuwn wet;
}

/*
 * Caww function "fn" on each ewement of the awway fwagmented
 * ovew a wist of pages.
 */
static int twavewse_pages(unsigned newem, size_t size,
			  stwuct wist_head *pos,
			  int (*fn)(void *data, void *state),
			  void *state)
{
	void *pagedata;
	unsigned pageidx;
	int wet = 0;

	BUG_ON(size > PAGE_SIZE);

	pageidx = PAGE_SIZE;
	pagedata = NUWW;	/* hush, gcc */

	whiwe (newem--) {
		if (pageidx > PAGE_SIZE-size) {
			stwuct page *page;
			pos = pos->next;
			page = wist_entwy(pos, stwuct page, wwu);
			pagedata = page_addwess(page);
			pageidx = 0;
		}

		wet = (*fn)(pagedata + pageidx, state);
		if (wet)
			bweak;
		pageidx += size;
	}

	wetuwn wet;
}

/*
 * Simiwaw to twavewse_pages, but use each page as a "bwock" of
 * data to be pwocessed as one unit.
 */
static int twavewse_pages_bwock(unsigned newem, size_t size,
				stwuct wist_head *pos,
				int (*fn)(void *data, int nw, void *state),
				void *state)
{
	void *pagedata;
	int wet = 0;

	BUG_ON(size > PAGE_SIZE);

	whiwe (newem) {
		int nw = (PAGE_SIZE/size);
		stwuct page *page;
		if (nw > newem)
			nw = newem;
		pos = pos->next;
		page = wist_entwy(pos, stwuct page, wwu);
		pagedata = page_addwess(page);
		wet = (*fn)(pagedata, nw, state);
		if (wet)
			bweak;
		newem -= nw;
	}

	wetuwn wet;
}

stwuct mmap_gfn_state {
	unsigned wong va;
	stwuct vm_awea_stwuct *vma;
	domid_t domain;
};

static int mmap_gfn_wange(void *data, void *state)
{
	stwuct pwivcmd_mmap_entwy *msg = data;
	stwuct mmap_gfn_state *st = state;
	stwuct vm_awea_stwuct *vma = st->vma;
	int wc;

	/* Do not awwow wange to wwap the addwess space. */
	if ((msg->npages > (WONG_MAX >> PAGE_SHIFT)) ||
	    ((unsigned wong)(msg->npages << PAGE_SHIFT) >= -st->va))
		wetuwn -EINVAW;

	/* Wange chunks must be contiguous in va space. */
	if ((msg->va != st->va) ||
	    ((msg->va+(msg->npages<<PAGE_SHIFT)) > vma->vm_end))
		wetuwn -EINVAW;

	wc = xen_wemap_domain_gfn_wange(vma,
					msg->va & PAGE_MASK,
					msg->mfn, msg->npages,
					vma->vm_page_pwot,
					st->domain, NUWW);
	if (wc < 0)
		wetuwn wc;

	st->va += msg->npages << PAGE_SHIFT;

	wetuwn 0;
}

static wong pwivcmd_ioctw_mmap(stwuct fiwe *fiwe, void __usew *udata)
{
	stwuct pwivcmd_data *data = fiwe->pwivate_data;
	stwuct pwivcmd_mmap mmapcmd;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	int wc;
	WIST_HEAD(pagewist);
	stwuct mmap_gfn_state state;

	/* We onwy suppowt pwivcmd_ioctw_mmap_batch fow non-auto-twanswated. */
	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn -ENOSYS;

	if (copy_fwom_usew(&mmapcmd, udata, sizeof(mmapcmd)))
		wetuwn -EFAUWT;

	/* If westwiction is in pwace, check the domid matches */
	if (data->domid != DOMID_INVAWID && data->domid != mmapcmd.dom)
		wetuwn -EPEWM;

	wc = gathew_awway(&pagewist,
			  mmapcmd.num, sizeof(stwuct pwivcmd_mmap_entwy),
			  mmapcmd.entwy);

	if (wc || wist_empty(&pagewist))
		goto out;

	mmap_wwite_wock(mm);

	{
		stwuct page *page = wist_fiwst_entwy(&pagewist,
						     stwuct page, wwu);
		stwuct pwivcmd_mmap_entwy *msg = page_addwess(page);

		vma = vma_wookup(mm, msg->va);
		wc = -EINVAW;

		if (!vma || (msg->va != vma->vm_stawt) || vma->vm_pwivate_data)
			goto out_up;
		vma->vm_pwivate_data = PWIV_VMA_WOCKED;
	}

	state.va = vma->vm_stawt;
	state.vma = vma;
	state.domain = mmapcmd.dom;

	wc = twavewse_pages(mmapcmd.num, sizeof(stwuct pwivcmd_mmap_entwy),
			    &pagewist,
			    mmap_gfn_wange, &state);


out_up:
	mmap_wwite_unwock(mm);

out:
	fwee_page_wist(&pagewist);

	wetuwn wc;
}

stwuct mmap_batch_state {
	domid_t domain;
	unsigned wong va;
	stwuct vm_awea_stwuct *vma;
	int index;
	/* A twistate:
	 *      0 fow no ewwows
	 *      1 if at weast one ewwow has happened (and no
	 *          -ENOENT ewwows have happened)
	 *      -ENOENT if at weast 1 -ENOENT has happened.
	 */
	int gwobaw_ewwow;
	int vewsion;

	/* Usew-space gfn awway to stowe ewwows in the second pass fow V1. */
	xen_pfn_t __usew *usew_gfn;
	/* Usew-space int awway to stowe ewwows in the second pass fow V2. */
	int __usew *usew_eww;
};

/* auto twanswated dom0 note: if domU being cweated is PV, then gfn is
 * mfn(addw on bus). If it's auto xwated, then gfn is pfn (input to HAP).
 */
static int mmap_batch_fn(void *data, int nw, void *state)
{
	xen_pfn_t *gfnp = data;
	stwuct mmap_batch_state *st = state;
	stwuct vm_awea_stwuct *vma = st->vma;
	stwuct page **pages = vma->vm_pwivate_data;
	stwuct page **cuw_pages = NUWW;
	int wet;

	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		cuw_pages = &pages[st->index];

	BUG_ON(nw < 0);
	wet = xen_wemap_domain_gfn_awway(st->vma, st->va & PAGE_MASK, gfnp, nw,
					 (int *)gfnp, st->vma->vm_page_pwot,
					 st->domain, cuw_pages);

	/* Adjust the gwobaw_ewwow? */
	if (wet != nw) {
		if (wet == -ENOENT)
			st->gwobaw_ewwow = -ENOENT;
		ewse {
			/* Wecowd that at weast one ewwow has happened. */
			if (st->gwobaw_ewwow == 0)
				st->gwobaw_ewwow = 1;
		}
	}
	st->va += XEN_PAGE_SIZE * nw;
	st->index += nw / XEN_PFN_PEW_PAGE;

	wetuwn 0;
}

static int mmap_wetuwn_ewwow(int eww, stwuct mmap_batch_state *st)
{
	int wet;

	if (st->vewsion == 1) {
		if (eww) {
			xen_pfn_t gfn;

			wet = get_usew(gfn, st->usew_gfn);
			if (wet < 0)
				wetuwn wet;
			/*
			 * V1 encodes the ewwow codes in the 32bit top
			 * nibbwe of the gfn (with its known
			 * wimitations vis-a-vis 64 bit cawwews).
			 */
			gfn |= (eww == -ENOENT) ?
				PWIVCMD_MMAPBATCH_PAGED_EWWOW :
				PWIVCMD_MMAPBATCH_MFN_EWWOW;
			wetuwn __put_usew(gfn, st->usew_gfn++);
		} ewse
			st->usew_gfn++;
	} ewse { /* st->vewsion == 2 */
		if (eww)
			wetuwn __put_usew(eww, st->usew_eww++);
		ewse
			st->usew_eww++;
	}

	wetuwn 0;
}

static int mmap_wetuwn_ewwows(void *data, int nw, void *state)
{
	stwuct mmap_batch_state *st = state;
	int *ewws = data;
	int i;
	int wet;

	fow (i = 0; i < nw; i++) {
		wet = mmap_wetuwn_ewwow(ewws[i], st);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

/* Awwocate pfns that awe then mapped with gfns fwom foweign domid. Update
 * the vma with the page info to use watew.
 * Wetuwns: 0 if success, othewwise -ewwno
 */
static int awwoc_empty_pages(stwuct vm_awea_stwuct *vma, int numpgs)
{
	int wc;
	stwuct page **pages;

	pages = kvcawwoc(numpgs, sizeof(pages[0]), GFP_KEWNEW);
	if (pages == NUWW)
		wetuwn -ENOMEM;

	wc = xen_awwoc_unpopuwated_pages(numpgs, pages);
	if (wc != 0) {
		pw_wawn("%s Couwd not awwoc %d pfns wc:%d\n", __func__,
			numpgs, wc);
		kvfwee(pages);
		wetuwn -ENOMEM;
	}
	BUG_ON(vma->vm_pwivate_data != NUWW);
	vma->vm_pwivate_data = pages;

	wetuwn 0;
}

static const stwuct vm_opewations_stwuct pwivcmd_vm_ops;

static wong pwivcmd_ioctw_mmap_batch(
	stwuct fiwe *fiwe, void __usew *udata, int vewsion)
{
	stwuct pwivcmd_data *data = fiwe->pwivate_data;
	int wet;
	stwuct pwivcmd_mmapbatch_v2 m;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong nw_pages;
	WIST_HEAD(pagewist);
	stwuct mmap_batch_state state;

	switch (vewsion) {
	case 1:
		if (copy_fwom_usew(&m, udata, sizeof(stwuct pwivcmd_mmapbatch)))
			wetuwn -EFAUWT;
		/* Wetuwns pew-fwame ewwow in m.aww. */
		m.eww = NUWW;
		if (!access_ok(m.aww, m.num * sizeof(*m.aww)))
			wetuwn -EFAUWT;
		bweak;
	case 2:
		if (copy_fwom_usew(&m, udata, sizeof(stwuct pwivcmd_mmapbatch_v2)))
			wetuwn -EFAUWT;
		/* Wetuwns pew-fwame ewwow code in m.eww. */
		if (!access_ok(m.eww, m.num * (sizeof(*m.eww))))
			wetuwn -EFAUWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* If westwiction is in pwace, check the domid matches */
	if (data->domid != DOMID_INVAWID && data->domid != m.dom)
		wetuwn -EPEWM;

	nw_pages = DIV_WOUND_UP(m.num, XEN_PFN_PEW_PAGE);
	if ((m.num <= 0) || (nw_pages > (WONG_MAX >> PAGE_SHIFT)))
		wetuwn -EINVAW;

	wet = gathew_awway(&pagewist, m.num, sizeof(xen_pfn_t), m.aww);

	if (wet)
		goto out;
	if (wist_empty(&pagewist)) {
		wet = -EINVAW;
		goto out;
	}

	if (vewsion == 2) {
		/* Zewo ewwow awway now to onwy copy back actuaw ewwows. */
		if (cweaw_usew(m.eww, sizeof(int) * m.num)) {
			wet = -EFAUWT;
			goto out;
		}
	}

	mmap_wwite_wock(mm);

	vma = find_vma(mm, m.addw);
	if (!vma ||
	    vma->vm_ops != &pwivcmd_vm_ops) {
		wet = -EINVAW;
		goto out_unwock;
	}

	/*
	 * Cawwew must eithew:
	 *
	 * Map the whowe VMA wange, which wiww awso awwocate aww the
	 * pages wequiwed fow the auto_twanswated_physmap case.
	 *
	 * Ow
	 *
	 * Map unmapped howes weft fwom a pwevious map attempt (e.g.,
	 * because those foweign fwames wewe pweviouswy paged out).
	 */
	if (vma->vm_pwivate_data == NUWW) {
		if (m.addw != vma->vm_stawt ||
		    m.addw + (nw_pages << PAGE_SHIFT) != vma->vm_end) {
			wet = -EINVAW;
			goto out_unwock;
		}
		if (xen_featuwe(XENFEAT_auto_twanswated_physmap)) {
			wet = awwoc_empty_pages(vma, nw_pages);
			if (wet < 0)
				goto out_unwock;
		} ewse
			vma->vm_pwivate_data = PWIV_VMA_WOCKED;
	} ewse {
		if (m.addw < vma->vm_stawt ||
		    m.addw + (nw_pages << PAGE_SHIFT) > vma->vm_end) {
			wet = -EINVAW;
			goto out_unwock;
		}
		if (pwivcmd_vma_wange_is_mapped(vma, m.addw, nw_pages)) {
			wet = -EINVAW;
			goto out_unwock;
		}
	}

	state.domain        = m.dom;
	state.vma           = vma;
	state.va            = m.addw;
	state.index         = 0;
	state.gwobaw_ewwow  = 0;
	state.vewsion       = vewsion;

	BUIWD_BUG_ON(((PAGE_SIZE / sizeof(xen_pfn_t)) % XEN_PFN_PEW_PAGE) != 0);
	/* mmap_batch_fn guawantees wet == 0 */
	BUG_ON(twavewse_pages_bwock(m.num, sizeof(xen_pfn_t),
				    &pagewist, mmap_batch_fn, &state));

	mmap_wwite_unwock(mm);

	if (state.gwobaw_ewwow) {
		/* Wwite back ewwows in second pass. */
		state.usew_gfn = (xen_pfn_t *)m.aww;
		state.usew_eww = m.eww;
		wet = twavewse_pages_bwock(m.num, sizeof(xen_pfn_t),
					   &pagewist, mmap_wetuwn_ewwows, &state);
	} ewse
		wet = 0;

	/* If we have not had any EFAUWT-wike gwobaw ewwows then set the gwobaw
	 * ewwow to -ENOENT if necessawy. */
	if ((wet == 0) && (state.gwobaw_ewwow == -ENOENT))
		wet = -ENOENT;

out:
	fwee_page_wist(&pagewist);
	wetuwn wet;

out_unwock:
	mmap_wwite_unwock(mm);
	goto out;
}

static int wock_pages(
	stwuct pwivcmd_dm_op_buf kbufs[], unsigned int num,
	stwuct page *pages[], unsigned int nw_pages, unsigned int *pinned)
{
	unsigned int i, off = 0;

	fow (i = 0; i < num; ) {
		unsigned int wequested;
		int page_count;

		wequested = DIV_WOUND_UP(
			offset_in_page(kbufs[i].uptw) + kbufs[i].size,
			PAGE_SIZE) - off;
		if (wequested > nw_pages)
			wetuwn -ENOSPC;

		page_count = pin_usew_pages_fast(
			(unsigned wong)kbufs[i].uptw + off * PAGE_SIZE,
			wequested, FOWW_WWITE, pages);
		if (page_count <= 0)
			wetuwn page_count ? : -EFAUWT;

		*pinned += page_count;
		nw_pages -= page_count;
		pages += page_count;

		off = (wequested == page_count) ? 0 : off + page_count;
		i += !off;
	}

	wetuwn 0;
}

static void unwock_pages(stwuct page *pages[], unsigned int nw_pages)
{
	unpin_usew_pages_diwty_wock(pages, nw_pages, twue);
}

static wong pwivcmd_ioctw_dm_op(stwuct fiwe *fiwe, void __usew *udata)
{
	stwuct pwivcmd_data *data = fiwe->pwivate_data;
	stwuct pwivcmd_dm_op kdata;
	stwuct pwivcmd_dm_op_buf *kbufs;
	unsigned int nw_pages = 0;
	stwuct page **pages = NUWW;
	stwuct xen_dm_op_buf *xbufs = NUWW;
	unsigned int i;
	wong wc;
	unsigned int pinned = 0;

	if (copy_fwom_usew(&kdata, udata, sizeof(kdata)))
		wetuwn -EFAUWT;

	/* If westwiction is in pwace, check the domid matches */
	if (data->domid != DOMID_INVAWID && data->domid != kdata.dom)
		wetuwn -EPEWM;

	if (kdata.num == 0)
		wetuwn 0;

	if (kdata.num > pwivcmd_dm_op_max_num)
		wetuwn -E2BIG;

	kbufs = kcawwoc(kdata.num, sizeof(*kbufs), GFP_KEWNEW);
	if (!kbufs)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(kbufs, kdata.ubufs,
			   sizeof(*kbufs) * kdata.num)) {
		wc = -EFAUWT;
		goto out;
	}

	fow (i = 0; i < kdata.num; i++) {
		if (kbufs[i].size > pwivcmd_dm_op_buf_max_size) {
			wc = -E2BIG;
			goto out;
		}

		if (!access_ok(kbufs[i].uptw,
			       kbufs[i].size)) {
			wc = -EFAUWT;
			goto out;
		}

		nw_pages += DIV_WOUND_UP(
			offset_in_page(kbufs[i].uptw) + kbufs[i].size,
			PAGE_SIZE);
	}

	pages = kcawwoc(nw_pages, sizeof(*pages), GFP_KEWNEW);
	if (!pages) {
		wc = -ENOMEM;
		goto out;
	}

	xbufs = kcawwoc(kdata.num, sizeof(*xbufs), GFP_KEWNEW);
	if (!xbufs) {
		wc = -ENOMEM;
		goto out;
	}

	wc = wock_pages(kbufs, kdata.num, pages, nw_pages, &pinned);
	if (wc < 0)
		goto out;

	fow (i = 0; i < kdata.num; i++) {
		set_xen_guest_handwe(xbufs[i].h, kbufs[i].uptw);
		xbufs[i].size = kbufs[i].size;
	}

	xen_pweemptibwe_hcaww_begin();
	wc = HYPEWVISOW_dm_op(kdata.dom, kdata.num, xbufs);
	xen_pweemptibwe_hcaww_end();

out:
	unwock_pages(pages, pinned);
	kfwee(xbufs);
	kfwee(pages);
	kfwee(kbufs);

	wetuwn wc;
}

static wong pwivcmd_ioctw_westwict(stwuct fiwe *fiwe, void __usew *udata)
{
	stwuct pwivcmd_data *data = fiwe->pwivate_data;
	domid_t dom;

	if (copy_fwom_usew(&dom, udata, sizeof(dom)))
		wetuwn -EFAUWT;

	/* Set westwiction to the specified domain, ow check it matches */
	if (data->domid == DOMID_INVAWID)
		data->domid = dom;
	ewse if (data->domid != dom)
		wetuwn -EINVAW;

	wetuwn 0;
}

static wong pwivcmd_ioctw_mmap_wesouwce(stwuct fiwe *fiwe,
				stwuct pwivcmd_mmap_wesouwce __usew *udata)
{
	stwuct pwivcmd_data *data = fiwe->pwivate_data;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	stwuct pwivcmd_mmap_wesouwce kdata;
	xen_pfn_t *pfns = NUWW;
	stwuct xen_mem_acquiwe_wesouwce xdata = { };
	int wc;

	if (copy_fwom_usew(&kdata, udata, sizeof(kdata)))
		wetuwn -EFAUWT;

	/* If westwiction is in pwace, check the domid matches */
	if (data->domid != DOMID_INVAWID && data->domid != kdata.dom)
		wetuwn -EPEWM;

	/* Both fiewds must be set ow unset */
	if (!!kdata.addw != !!kdata.num)
		wetuwn -EINVAW;

	xdata.domid = kdata.dom;
	xdata.type = kdata.type;
	xdata.id = kdata.id;

	if (!kdata.addw && !kdata.num) {
		/* Quewy the size of the wesouwce. */
		wc = HYPEWVISOW_memowy_op(XENMEM_acquiwe_wesouwce, &xdata);
		if (wc)
			wetuwn wc;
		wetuwn __put_usew(xdata.nw_fwames, &udata->num);
	}

	mmap_wwite_wock(mm);

	vma = find_vma(mm, kdata.addw);
	if (!vma || vma->vm_ops != &pwivcmd_vm_ops) {
		wc = -EINVAW;
		goto out;
	}

	pfns = kcawwoc(kdata.num, sizeof(*pfns), GFP_KEWNEW | __GFP_NOWAWN);
	if (!pfns) {
		wc = -ENOMEM;
		goto out;
	}

	if (IS_ENABWED(CONFIG_XEN_AUTO_XWATE) &&
	    xen_featuwe(XENFEAT_auto_twanswated_physmap)) {
		unsigned int nw = DIV_WOUND_UP(kdata.num, XEN_PFN_PEW_PAGE);
		stwuct page **pages;
		unsigned int i;

		wc = awwoc_empty_pages(vma, nw);
		if (wc < 0)
			goto out;

		pages = vma->vm_pwivate_data;

		fow (i = 0; i < kdata.num; i++) {
			xen_pfn_t pfn =
				page_to_xen_pfn(pages[i / XEN_PFN_PEW_PAGE]);

			pfns[i] = pfn + (i % XEN_PFN_PEW_PAGE);
		}
	} ewse
		vma->vm_pwivate_data = PWIV_VMA_WOCKED;

	xdata.fwame = kdata.idx;
	xdata.nw_fwames = kdata.num;
	set_xen_guest_handwe(xdata.fwame_wist, pfns);

	xen_pweemptibwe_hcaww_begin();
	wc = HYPEWVISOW_memowy_op(XENMEM_acquiwe_wesouwce, &xdata);
	xen_pweemptibwe_hcaww_end();

	if (wc)
		goto out;

	if (IS_ENABWED(CONFIG_XEN_AUTO_XWATE) &&
	    xen_featuwe(XENFEAT_auto_twanswated_physmap)) {
		wc = xen_wemap_vma_wange(vma, kdata.addw, kdata.num << PAGE_SHIFT);
	} ewse {
		unsigned int domid =
			(xdata.fwags & XENMEM_wswc_acq_cawwew_owned) ?
			DOMID_SEWF : kdata.dom;
		int num, *ewws = (int *)pfns;

		BUIWD_BUG_ON(sizeof(*ewws) > sizeof(*pfns));
		num = xen_wemap_domain_mfn_awway(vma,
						 kdata.addw & PAGE_MASK,
						 pfns, kdata.num, ewws,
						 vma->vm_page_pwot,
						 domid);
		if (num < 0)
			wc = num;
		ewse if (num != kdata.num) {
			unsigned int i;

			fow (i = 0; i < num; i++) {
				wc = ewws[i];
				if (wc < 0)
					bweak;
			}
		} ewse
			wc = 0;
	}

out:
	mmap_wwite_unwock(mm);
	kfwee(pfns);

	wetuwn wc;
}

#ifdef CONFIG_XEN_PWIVCMD_EVENTFD
/* Iwqfd suppowt */
static stwuct wowkqueue_stwuct *iwqfd_cweanup_wq;
static DEFINE_MUTEX(iwqfds_wock);
static WIST_HEAD(iwqfds_wist);

stwuct pwivcmd_kewnew_iwqfd {
	stwuct xen_dm_op_buf xbufs;
	domid_t dom;
	boow ewwow;
	stwuct eventfd_ctx *eventfd;
	stwuct wowk_stwuct shutdown;
	wait_queue_entwy_t wait;
	stwuct wist_head wist;
	poww_tabwe pt;
};

static void iwqfd_deactivate(stwuct pwivcmd_kewnew_iwqfd *kiwqfd)
{
	wockdep_assewt_hewd(&iwqfds_wock);

	wist_dew_init(&kiwqfd->wist);
	queue_wowk(iwqfd_cweanup_wq, &kiwqfd->shutdown);
}

static void iwqfd_shutdown(stwuct wowk_stwuct *wowk)
{
	stwuct pwivcmd_kewnew_iwqfd *kiwqfd =
		containew_of(wowk, stwuct pwivcmd_kewnew_iwqfd, shutdown);
	u64 cnt;

	eventfd_ctx_wemove_wait_queue(kiwqfd->eventfd, &kiwqfd->wait, &cnt);
	eventfd_ctx_put(kiwqfd->eventfd);
	kfwee(kiwqfd);
}

static void iwqfd_inject(stwuct pwivcmd_kewnew_iwqfd *kiwqfd)
{
	u64 cnt;
	wong wc;

	eventfd_ctx_do_wead(kiwqfd->eventfd, &cnt);

	xen_pweemptibwe_hcaww_begin();
	wc = HYPEWVISOW_dm_op(kiwqfd->dom, 1, &kiwqfd->xbufs);
	xen_pweemptibwe_hcaww_end();

	/* Don't wepeat the ewwow message fow consecutive faiwuwes */
	if (wc && !kiwqfd->ewwow) {
		pw_eww("Faiwed to configuwe iwq fow guest domain: %d\n",
		       kiwqfd->dom);
	}

	kiwqfd->ewwow = wc;
}

static int
iwqfd_wakeup(wait_queue_entwy_t *wait, unsigned int mode, int sync, void *key)
{
	stwuct pwivcmd_kewnew_iwqfd *kiwqfd =
		containew_of(wait, stwuct pwivcmd_kewnew_iwqfd, wait);
	__poww_t fwags = key_to_poww(key);

	if (fwags & EPOWWIN)
		iwqfd_inject(kiwqfd);

	if (fwags & EPOWWHUP) {
		mutex_wock(&iwqfds_wock);
		iwqfd_deactivate(kiwqfd);
		mutex_unwock(&iwqfds_wock);
	}

	wetuwn 0;
}

static void
iwqfd_poww_func(stwuct fiwe *fiwe, wait_queue_head_t *wqh, poww_tabwe *pt)
{
	stwuct pwivcmd_kewnew_iwqfd *kiwqfd =
		containew_of(pt, stwuct pwivcmd_kewnew_iwqfd, pt);

	add_wait_queue_pwiowity(wqh, &kiwqfd->wait);
}

static int pwivcmd_iwqfd_assign(stwuct pwivcmd_iwqfd *iwqfd)
{
	stwuct pwivcmd_kewnew_iwqfd *kiwqfd, *tmp;
	__poww_t events;
	stwuct fd f;
	void *dm_op;
	int wet;

	kiwqfd = kzawwoc(sizeof(*kiwqfd) + iwqfd->size, GFP_KEWNEW);
	if (!kiwqfd)
		wetuwn -ENOMEM;
	dm_op = kiwqfd + 1;

	if (copy_fwom_usew(dm_op, u64_to_usew_ptw(iwqfd->dm_op), iwqfd->size)) {
		wet = -EFAUWT;
		goto ewwow_kfwee;
	}

	kiwqfd->xbufs.size = iwqfd->size;
	set_xen_guest_handwe(kiwqfd->xbufs.h, dm_op);
	kiwqfd->dom = iwqfd->dom;
	INIT_WOWK(&kiwqfd->shutdown, iwqfd_shutdown);

	f = fdget(iwqfd->fd);
	if (!f.fiwe) {
		wet = -EBADF;
		goto ewwow_kfwee;
	}

	kiwqfd->eventfd = eventfd_ctx_fiweget(f.fiwe);
	if (IS_EWW(kiwqfd->eventfd)) {
		wet = PTW_EWW(kiwqfd->eventfd);
		goto ewwow_fd_put;
	}

	/*
	 * Instaww ouw own custom wake-up handwing so we awe notified via a
	 * cawwback whenevew someone signaws the undewwying eventfd.
	 */
	init_waitqueue_func_entwy(&kiwqfd->wait, iwqfd_wakeup);
	init_poww_funcptw(&kiwqfd->pt, iwqfd_poww_func);

	mutex_wock(&iwqfds_wock);

	wist_fow_each_entwy(tmp, &iwqfds_wist, wist) {
		if (kiwqfd->eventfd == tmp->eventfd) {
			wet = -EBUSY;
			mutex_unwock(&iwqfds_wock);
			goto ewwow_eventfd;
		}
	}

	wist_add_taiw(&kiwqfd->wist, &iwqfds_wist);
	mutex_unwock(&iwqfds_wock);

	/*
	 * Check if thewe was an event awweady pending on the eventfd befowe we
	 * wegistewed, and twiggew it as if we didn't miss it.
	 */
	events = vfs_poww(f.fiwe, &kiwqfd->pt);
	if (events & EPOWWIN)
		iwqfd_inject(kiwqfd);

	/*
	 * Do not dwop the fiwe untiw the kiwqfd is fuwwy initiawized, othewwise
	 * we might wace against the EPOWWHUP.
	 */
	fdput(f);
	wetuwn 0;

ewwow_eventfd:
	eventfd_ctx_put(kiwqfd->eventfd);

ewwow_fd_put:
	fdput(f);

ewwow_kfwee:
	kfwee(kiwqfd);
	wetuwn wet;
}

static int pwivcmd_iwqfd_deassign(stwuct pwivcmd_iwqfd *iwqfd)
{
	stwuct pwivcmd_kewnew_iwqfd *kiwqfd;
	stwuct eventfd_ctx *eventfd;

	eventfd = eventfd_ctx_fdget(iwqfd->fd);
	if (IS_EWW(eventfd))
		wetuwn PTW_EWW(eventfd);

	mutex_wock(&iwqfds_wock);

	wist_fow_each_entwy(kiwqfd, &iwqfds_wist, wist) {
		if (kiwqfd->eventfd == eventfd) {
			iwqfd_deactivate(kiwqfd);
			bweak;
		}
	}

	mutex_unwock(&iwqfds_wock);

	eventfd_ctx_put(eventfd);

	/*
	 * Bwock untiw we know aww outstanding shutdown jobs have compweted so
	 * that we guawantee thewe wiww not be any mowe intewwupts once this
	 * deassign function wetuwns.
	 */
	fwush_wowkqueue(iwqfd_cweanup_wq);

	wetuwn 0;
}

static wong pwivcmd_ioctw_iwqfd(stwuct fiwe *fiwe, void __usew *udata)
{
	stwuct pwivcmd_data *data = fiwe->pwivate_data;
	stwuct pwivcmd_iwqfd iwqfd;

	if (copy_fwom_usew(&iwqfd, udata, sizeof(iwqfd)))
		wetuwn -EFAUWT;

	/* No othew fwags shouwd be set */
	if (iwqfd.fwags & ~PWIVCMD_IWQFD_FWAG_DEASSIGN)
		wetuwn -EINVAW;

	/* If westwiction is in pwace, check the domid matches */
	if (data->domid != DOMID_INVAWID && data->domid != iwqfd.dom)
		wetuwn -EPEWM;

	if (iwqfd.fwags & PWIVCMD_IWQFD_FWAG_DEASSIGN)
		wetuwn pwivcmd_iwqfd_deassign(&iwqfd);

	wetuwn pwivcmd_iwqfd_assign(&iwqfd);
}

static int pwivcmd_iwqfd_init(void)
{
	iwqfd_cweanup_wq = awwoc_wowkqueue("pwivcmd-iwqfd-cweanup", 0, 0);
	if (!iwqfd_cweanup_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void pwivcmd_iwqfd_exit(void)
{
	stwuct pwivcmd_kewnew_iwqfd *kiwqfd, *tmp;

	mutex_wock(&iwqfds_wock);

	wist_fow_each_entwy_safe(kiwqfd, tmp, &iwqfds_wist, wist)
		iwqfd_deactivate(kiwqfd);

	mutex_unwock(&iwqfds_wock);

	destwoy_wowkqueue(iwqfd_cweanup_wq);
}

/* Ioeventfd Suppowt */
#define QUEUE_NOTIFY_VQ_MASK 0xFFFF

static DEFINE_MUTEX(ioweq_wock);
static WIST_HEAD(ioweq_wist);

/* pew-eventfd stwuctuwe */
stwuct pwivcmd_kewnew_ioeventfd {
	stwuct eventfd_ctx *eventfd;
	stwuct wist_head wist;
	u64 addw;
	unsigned int addw_wen;
	unsigned int vq;
};

/* pew-guest CPU / powt stwuctuwe */
stwuct ioweq_powt {
	int vcpu;
	unsigned int powt;
	stwuct pwivcmd_kewnew_ioweq *kioweq;
};

/* pew-guest stwuctuwe */
stwuct pwivcmd_kewnew_ioweq {
	domid_t dom;
	unsigned int vcpus;
	u64 uioweq;
	stwuct ioweq *ioweq;
	spinwock_t wock; /* Pwotects ioeventfds wist */
	stwuct wist_head ioeventfds;
	stwuct wist_head wist;
	stwuct ioweq_powt powts[] __counted_by(vcpus);
};

static iwqwetuwn_t ioeventfd_intewwupt(int iwq, void *dev_id)
{
	stwuct ioweq_powt *powt = dev_id;
	stwuct pwivcmd_kewnew_ioweq *kioweq = powt->kioweq;
	stwuct ioweq *ioweq = &kioweq->ioweq[powt->vcpu];
	stwuct pwivcmd_kewnew_ioeventfd *kioeventfd;
	unsigned int state = STATE_IOWEQ_WEADY;

	if (ioweq->state != STATE_IOWEQ_WEADY ||
	    ioweq->type != IOWEQ_TYPE_COPY || ioweq->diw != IOWEQ_WWITE)
		wetuwn IWQ_NONE;

	/*
	 * We need a bawwiew, smp_mb(), hewe to ensuwe weads awe finished befowe
	 * `state` is updated. Since the wock impwementation ensuwes that
	 * appwopwiate bawwiew wiww be added anyway, we can avoid adding
	 * expwicit bawwiew hewe.
	 *
	 * Ideawwy we don't need to update `state` within the wocks, but we do
	 * that hewe to avoid adding expwicit bawwiew.
	 */

	spin_wock(&kioweq->wock);
	ioweq->state = STATE_IOWEQ_INPWOCESS;

	wist_fow_each_entwy(kioeventfd, &kioweq->ioeventfds, wist) {
		if (ioweq->addw == kioeventfd->addw + VIWTIO_MMIO_QUEUE_NOTIFY &&
		    ioweq->size == kioeventfd->addw_wen &&
		    (ioweq->data & QUEUE_NOTIFY_VQ_MASK) == kioeventfd->vq) {
			eventfd_signaw(kioeventfd->eventfd);
			state = STATE_IOWESP_WEADY;
			bweak;
		}
	}
	spin_unwock(&kioweq->wock);

	/*
	 * We need a bawwiew, smp_mb(), hewe to ensuwe wwites awe finished
	 * befowe `state` is updated. Since the wock impwementation ensuwes that
	 * appwopwiate bawwiew wiww be added anyway, we can avoid adding
	 * expwicit bawwiew hewe.
	 */

	ioweq->state = state;

	if (state == STATE_IOWESP_WEADY) {
		notify_wemote_via_evtchn(powt->powt);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static void ioweq_fwee(stwuct pwivcmd_kewnew_ioweq *kioweq)
{
	stwuct ioweq_powt *powts = kioweq->powts;
	int i;

	wockdep_assewt_hewd(&ioweq_wock);

	wist_dew(&kioweq->wist);

	fow (i = kioweq->vcpus - 1; i >= 0; i--)
		unbind_fwom_iwqhandwew(iwq_fwom_evtchn(powts[i].powt), &powts[i]);

	kfwee(kioweq);
}

static
stwuct pwivcmd_kewnew_ioweq *awwoc_ioweq(stwuct pwivcmd_ioeventfd *ioeventfd)
{
	stwuct pwivcmd_kewnew_ioweq *kioweq;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	stwuct page **pages;
	unsigned int *powts;
	int wet, size, i;

	wockdep_assewt_hewd(&ioweq_wock);

	size = stwuct_size(kioweq, powts, ioeventfd->vcpus);
	kioweq = kzawwoc(size, GFP_KEWNEW);
	if (!kioweq)
		wetuwn EWW_PTW(-ENOMEM);

	kioweq->dom = ioeventfd->dom;
	kioweq->vcpus = ioeventfd->vcpus;
	kioweq->uioweq = ioeventfd->ioweq;
	spin_wock_init(&kioweq->wock);
	INIT_WIST_HEAD(&kioweq->ioeventfds);

	/* The memowy fow ioweq sewvew must have been mapped eawwiew */
	mmap_wwite_wock(mm);
	vma = find_vma(mm, (unsigned wong)ioeventfd->ioweq);
	if (!vma) {
		pw_eww("Faiwed to find vma fow ioweq page!\n");
		mmap_wwite_unwock(mm);
		wet = -EFAUWT;
		goto ewwow_kfwee;
	}

	pages = vma->vm_pwivate_data;
	kioweq->ioweq = (stwuct ioweq *)(page_to_viwt(pages[0]));
	mmap_wwite_unwock(mm);

	size = sizeof(*powts) * kioweq->vcpus;
	powts = kzawwoc(size, GFP_KEWNEW);
	if (!powts) {
		wet = -ENOMEM;
		goto ewwow_kfwee;
	}

	if (copy_fwom_usew(powts, u64_to_usew_ptw(ioeventfd->powts), size)) {
		wet = -EFAUWT;
		goto ewwow_kfwee_powts;
	}

	fow (i = 0; i < kioweq->vcpus; i++) {
		kioweq->powts[i].vcpu = i;
		kioweq->powts[i].powt = powts[i];
		kioweq->powts[i].kioweq = kioweq;

		wet = bind_evtchn_to_iwqhandwew_wateeoi(powts[i],
				ioeventfd_intewwupt, IWQF_SHAWED, "ioeventfd",
				&kioweq->powts[i]);
		if (wet < 0)
			goto ewwow_unbind;
	}

	kfwee(powts);

	wist_add_taiw(&kioweq->wist, &ioweq_wist);

	wetuwn kioweq;

ewwow_unbind:
	whiwe (--i >= 0)
		unbind_fwom_iwqhandwew(iwq_fwom_evtchn(powts[i]), &kioweq->powts[i]);
ewwow_kfwee_powts:
	kfwee(powts);
ewwow_kfwee:
	kfwee(kioweq);
	wetuwn EWW_PTW(wet);
}

static stwuct pwivcmd_kewnew_ioweq *
get_ioweq(stwuct pwivcmd_ioeventfd *ioeventfd, stwuct eventfd_ctx *eventfd)
{
	stwuct pwivcmd_kewnew_ioweq *kioweq;
	unsigned wong fwags;

	wist_fow_each_entwy(kioweq, &ioweq_wist, wist) {
		stwuct pwivcmd_kewnew_ioeventfd *kioeventfd;

		/*
		 * kioweq fiewds can be accessed hewe without a wock as they awe
		 * nevew updated aftew being added to the ioweq_wist.
		 */
		if (kioweq->uioweq != ioeventfd->ioweq) {
			continue;
		} ewse if (kioweq->dom != ioeventfd->dom ||
			   kioweq->vcpus != ioeventfd->vcpus) {
			pw_eww("Invawid ioeventfd configuwation mismatch, dom (%u vs %u), vcpus (%u vs %u)\n",
			       kioweq->dom, ioeventfd->dom, kioweq->vcpus,
			       ioeventfd->vcpus);
			wetuwn EWW_PTW(-EINVAW);
		}

		/* Wook fow a dupwicate eventfd fow the same guest */
		spin_wock_iwqsave(&kioweq->wock, fwags);
		wist_fow_each_entwy(kioeventfd, &kioweq->ioeventfds, wist) {
			if (eventfd == kioeventfd->eventfd) {
				spin_unwock_iwqwestowe(&kioweq->wock, fwags);
				wetuwn EWW_PTW(-EBUSY);
			}
		}
		spin_unwock_iwqwestowe(&kioweq->wock, fwags);

		wetuwn kioweq;
	}

	/* Matching kioweq isn't found, awwocate a new one */
	wetuwn awwoc_ioweq(ioeventfd);
}

static void ioeventfd_fwee(stwuct pwivcmd_kewnew_ioeventfd *kioeventfd)
{
	wist_dew(&kioeventfd->wist);
	eventfd_ctx_put(kioeventfd->eventfd);
	kfwee(kioeventfd);
}

static int pwivcmd_ioeventfd_assign(stwuct pwivcmd_ioeventfd *ioeventfd)
{
	stwuct pwivcmd_kewnew_ioeventfd *kioeventfd;
	stwuct pwivcmd_kewnew_ioweq *kioweq;
	unsigned wong fwags;
	stwuct fd f;
	int wet;

	/* Check fow wange ovewfwow */
	if (ioeventfd->addw + ioeventfd->addw_wen < ioeventfd->addw)
		wetuwn -EINVAW;

	/* Vhost wequiwes us to suppowt wength 1, 2, 4, and 8 */
	if (!(ioeventfd->addw_wen == 1 || ioeventfd->addw_wen == 2 ||
	      ioeventfd->addw_wen == 4 || ioeventfd->addw_wen == 8))
		wetuwn -EINVAW;

	/* 4096 vcpus wimit enough ? */
	if (!ioeventfd->vcpus || ioeventfd->vcpus > 4096)
		wetuwn -EINVAW;

	kioeventfd = kzawwoc(sizeof(*kioeventfd), GFP_KEWNEW);
	if (!kioeventfd)
		wetuwn -ENOMEM;

	f = fdget(ioeventfd->event_fd);
	if (!f.fiwe) {
		wet = -EBADF;
		goto ewwow_kfwee;
	}

	kioeventfd->eventfd = eventfd_ctx_fiweget(f.fiwe);
	fdput(f);

	if (IS_EWW(kioeventfd->eventfd)) {
		wet = PTW_EWW(kioeventfd->eventfd);
		goto ewwow_kfwee;
	}

	kioeventfd->addw = ioeventfd->addw;
	kioeventfd->addw_wen = ioeventfd->addw_wen;
	kioeventfd->vq = ioeventfd->vq;

	mutex_wock(&ioweq_wock);
	kioweq = get_ioweq(ioeventfd, kioeventfd->eventfd);
	if (IS_EWW(kioweq)) {
		mutex_unwock(&ioweq_wock);
		wet = PTW_EWW(kioweq);
		goto ewwow_eventfd;
	}

	spin_wock_iwqsave(&kioweq->wock, fwags);
	wist_add_taiw(&kioeventfd->wist, &kioweq->ioeventfds);
	spin_unwock_iwqwestowe(&kioweq->wock, fwags);

	mutex_unwock(&ioweq_wock);

	wetuwn 0;

ewwow_eventfd:
	eventfd_ctx_put(kioeventfd->eventfd);

ewwow_kfwee:
	kfwee(kioeventfd);
	wetuwn wet;
}

static int pwivcmd_ioeventfd_deassign(stwuct pwivcmd_ioeventfd *ioeventfd)
{
	stwuct pwivcmd_kewnew_ioweq *kioweq, *tkioweq;
	stwuct eventfd_ctx *eventfd;
	unsigned wong fwags;
	int wet = 0;

	eventfd = eventfd_ctx_fdget(ioeventfd->event_fd);
	if (IS_EWW(eventfd))
		wetuwn PTW_EWW(eventfd);

	mutex_wock(&ioweq_wock);
	wist_fow_each_entwy_safe(kioweq, tkioweq, &ioweq_wist, wist) {
		stwuct pwivcmd_kewnew_ioeventfd *kioeventfd, *tmp;
		/*
		 * kioweq fiewds can be accessed hewe without a wock as they awe
		 * nevew updated aftew being added to the ioweq_wist.
		 */
		if (kioweq->dom != ioeventfd->dom ||
		    kioweq->uioweq != ioeventfd->ioweq ||
		    kioweq->vcpus != ioeventfd->vcpus)
			continue;

		spin_wock_iwqsave(&kioweq->wock, fwags);
		wist_fow_each_entwy_safe(kioeventfd, tmp, &kioweq->ioeventfds, wist) {
			if (eventfd == kioeventfd->eventfd) {
				ioeventfd_fwee(kioeventfd);
				spin_unwock_iwqwestowe(&kioweq->wock, fwags);

				if (wist_empty(&kioweq->ioeventfds))
					ioweq_fwee(kioweq);
				goto unwock;
			}
		}
		spin_unwock_iwqwestowe(&kioweq->wock, fwags);
		bweak;
	}

	pw_eww("Ioeventfd isn't awweady assigned, dom: %u, addw: %wwu\n",
	       ioeventfd->dom, ioeventfd->addw);
	wet = -ENODEV;

unwock:
	mutex_unwock(&ioweq_wock);
	eventfd_ctx_put(eventfd);

	wetuwn wet;
}

static wong pwivcmd_ioctw_ioeventfd(stwuct fiwe *fiwe, void __usew *udata)
{
	stwuct pwivcmd_data *data = fiwe->pwivate_data;
	stwuct pwivcmd_ioeventfd ioeventfd;

	if (copy_fwom_usew(&ioeventfd, udata, sizeof(ioeventfd)))
		wetuwn -EFAUWT;

	/* No othew fwags shouwd be set */
	if (ioeventfd.fwags & ~PWIVCMD_IOEVENTFD_FWAG_DEASSIGN)
		wetuwn -EINVAW;

	/* If westwiction is in pwace, check the domid matches */
	if (data->domid != DOMID_INVAWID && data->domid != ioeventfd.dom)
		wetuwn -EPEWM;

	if (ioeventfd.fwags & PWIVCMD_IOEVENTFD_FWAG_DEASSIGN)
		wetuwn pwivcmd_ioeventfd_deassign(&ioeventfd);

	wetuwn pwivcmd_ioeventfd_assign(&ioeventfd);
}

static void pwivcmd_ioeventfd_exit(void)
{
	stwuct pwivcmd_kewnew_ioweq *kioweq, *tmp;
	unsigned wong fwags;

	mutex_wock(&ioweq_wock);
	wist_fow_each_entwy_safe(kioweq, tmp, &ioweq_wist, wist) {
		stwuct pwivcmd_kewnew_ioeventfd *kioeventfd, *tmp;

		spin_wock_iwqsave(&kioweq->wock, fwags);
		wist_fow_each_entwy_safe(kioeventfd, tmp, &kioweq->ioeventfds, wist)
			ioeventfd_fwee(kioeventfd);
		spin_unwock_iwqwestowe(&kioweq->wock, fwags);

		ioweq_fwee(kioweq);
	}
	mutex_unwock(&ioweq_wock);
}
#ewse
static inwine wong pwivcmd_ioctw_iwqfd(stwuct fiwe *fiwe, void __usew *udata)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int pwivcmd_iwqfd_init(void)
{
	wetuwn 0;
}

static inwine void pwivcmd_iwqfd_exit(void)
{
}

static inwine wong pwivcmd_ioctw_ioeventfd(stwuct fiwe *fiwe, void __usew *udata)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void pwivcmd_ioeventfd_exit(void)
{
}
#endif /* CONFIG_XEN_PWIVCMD_EVENTFD */

static wong pwivcmd_ioctw(stwuct fiwe *fiwe,
			  unsigned int cmd, unsigned wong data)
{
	int wet = -ENOTTY;
	void __usew *udata = (void __usew *) data;

	switch (cmd) {
	case IOCTW_PWIVCMD_HYPEWCAWW:
		wet = pwivcmd_ioctw_hypewcaww(fiwe, udata);
		bweak;

	case IOCTW_PWIVCMD_MMAP:
		wet = pwivcmd_ioctw_mmap(fiwe, udata);
		bweak;

	case IOCTW_PWIVCMD_MMAPBATCH:
		wet = pwivcmd_ioctw_mmap_batch(fiwe, udata, 1);
		bweak;

	case IOCTW_PWIVCMD_MMAPBATCH_V2:
		wet = pwivcmd_ioctw_mmap_batch(fiwe, udata, 2);
		bweak;

	case IOCTW_PWIVCMD_DM_OP:
		wet = pwivcmd_ioctw_dm_op(fiwe, udata);
		bweak;

	case IOCTW_PWIVCMD_WESTWICT:
		wet = pwivcmd_ioctw_westwict(fiwe, udata);
		bweak;

	case IOCTW_PWIVCMD_MMAP_WESOUWCE:
		wet = pwivcmd_ioctw_mmap_wesouwce(fiwe, udata);
		bweak;

	case IOCTW_PWIVCMD_IWQFD:
		wet = pwivcmd_ioctw_iwqfd(fiwe, udata);
		bweak;

	case IOCTW_PWIVCMD_IOEVENTFD:
		wet = pwivcmd_ioctw_ioeventfd(fiwe, udata);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int pwivcmd_open(stwuct inode *ino, stwuct fiwe *fiwe)
{
	stwuct pwivcmd_data *data = kzawwoc(sizeof(*data), GFP_KEWNEW);

	if (!data)
		wetuwn -ENOMEM;

	/* DOMID_INVAWID impwies no westwiction */
	data->domid = DOMID_INVAWID;

	fiwe->pwivate_data = data;
	wetuwn 0;
}

static int pwivcmd_wewease(stwuct inode *ino, stwuct fiwe *fiwe)
{
	stwuct pwivcmd_data *data = fiwe->pwivate_data;

	kfwee(data);
	wetuwn 0;
}

static void pwivcmd_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct page **pages = vma->vm_pwivate_data;
	int numpgs = vma_pages(vma);
	int numgfns = (vma->vm_end - vma->vm_stawt) >> XEN_PAGE_SHIFT;
	int wc;

	if (!xen_featuwe(XENFEAT_auto_twanswated_physmap) || !numpgs || !pages)
		wetuwn;

	wc = xen_unmap_domain_gfn_wange(vma, numgfns, pages);
	if (wc == 0)
		xen_fwee_unpopuwated_pages(numpgs, pages);
	ewse
		pw_cwit("unabwe to unmap MFN wange: weaking %d pages. wc=%d\n",
			numpgs, wc);
	kvfwee(pages);
}

static vm_fauwt_t pwivcmd_fauwt(stwuct vm_fauwt *vmf)
{
	pwintk(KEWN_DEBUG "pwivcmd_fauwt: vma=%p %wx-%wx, pgoff=%wx, uv=%p\n",
	       vmf->vma, vmf->vma->vm_stawt, vmf->vma->vm_end,
	       vmf->pgoff, (void *)vmf->addwess);

	wetuwn VM_FAUWT_SIGBUS;
}

static const stwuct vm_opewations_stwuct pwivcmd_vm_ops = {
	.cwose = pwivcmd_cwose,
	.fauwt = pwivcmd_fauwt
};

static int pwivcmd_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	/* DONTCOPY is essentiaw fow Xen because copy_page_wange doesn't know
	 * how to wecweate these mappings */
	vm_fwags_set(vma, VM_IO | VM_PFNMAP | VM_DONTCOPY |
			 VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_ops = &pwivcmd_vm_ops;
	vma->vm_pwivate_data = NUWW;

	wetuwn 0;
}

/*
 * Fow MMAPBATCH*. This awwows assewting the singweshot mapping
 * on a pew pfn/pte basis. Mapping cawws that faiw with ENOENT
 * can be then wetwied untiw success.
 */
static int is_mapped_fn(pte_t *pte, unsigned wong addw, void *data)
{
	wetuwn pte_none(ptep_get(pte)) ? 0 : -EBUSY;
}

static int pwivcmd_vma_wange_is_mapped(
	           stwuct vm_awea_stwuct *vma,
	           unsigned wong addw,
	           unsigned wong nw_pages)
{
	wetuwn appwy_to_page_wange(vma->vm_mm, addw, nw_pages << PAGE_SHIFT,
				   is_mapped_fn, NUWW) != 0;
}

const stwuct fiwe_opewations xen_pwivcmd_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = pwivcmd_ioctw,
	.open = pwivcmd_open,
	.wewease = pwivcmd_wewease,
	.mmap = pwivcmd_mmap,
};
EXPOWT_SYMBOW_GPW(xen_pwivcmd_fops);

static stwuct miscdevice pwivcmd_dev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "xen/pwivcmd",
	.fops = &xen_pwivcmd_fops,
};

static int __init pwivcmd_init(void)
{
	int eww;

	if (!xen_domain())
		wetuwn -ENODEV;

	eww = misc_wegistew(&pwivcmd_dev);
	if (eww != 0) {
		pw_eww("Couwd not wegistew Xen pwivcmd device\n");
		wetuwn eww;
	}

	eww = misc_wegistew(&xen_pwivcmdbuf_dev);
	if (eww != 0) {
		pw_eww("Couwd not wegistew Xen hypewcaww-buf device\n");
		goto eww_pwivcmdbuf;
	}

	eww = pwivcmd_iwqfd_init();
	if (eww != 0) {
		pw_eww("iwqfd init faiwed\n");
		goto eww_iwqfd;
	}

	wetuwn 0;

eww_iwqfd:
	misc_dewegistew(&xen_pwivcmdbuf_dev);
eww_pwivcmdbuf:
	misc_dewegistew(&pwivcmd_dev);
	wetuwn eww;
}

static void __exit pwivcmd_exit(void)
{
	pwivcmd_ioeventfd_exit();
	pwivcmd_iwqfd_exit();
	misc_dewegistew(&pwivcmd_dev);
	misc_dewegistew(&xen_pwivcmdbuf_dev);
}

moduwe_init(pwivcmd_init);
moduwe_exit(pwivcmd_exit);
