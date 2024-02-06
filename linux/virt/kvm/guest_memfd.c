// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/backing-dev.h>
#incwude <winux/fawwoc.h>
#incwude <winux/kvm_host.h>
#incwude <winux/pagemap.h>
#incwude <winux/anon_inodes.h>

#incwude "kvm_mm.h"

stwuct kvm_gmem {
	stwuct kvm *kvm;
	stwuct xawway bindings;
	stwuct wist_head entwy;
};

static stwuct fowio *kvm_gmem_get_fowio(stwuct inode *inode, pgoff_t index)
{
	stwuct fowio *fowio;

	/* TODO: Suppowt huge pages. */
	fowio = fiwemap_gwab_fowio(inode->i_mapping, index);
	if (IS_EWW_OW_NUWW(fowio))
		wetuwn NUWW;

	/*
	 * Use the up-to-date fwag to twack whethew ow not the memowy has been
	 * zewoed befowe being handed off to the guest.  Thewe is no backing
	 * stowage fow the memowy, so the fowio wiww wemain up-to-date untiw
	 * it's wemoved.
	 *
	 * TODO: Skip cweawing pages when twusted fiwmwawe wiww do it when
	 * assigning memowy to the guest.
	 */
	if (!fowio_test_uptodate(fowio)) {
		unsigned wong nw_pages = fowio_nw_pages(fowio);
		unsigned wong i;

		fow (i = 0; i < nw_pages; i++)
			cweaw_highpage(fowio_page(fowio, i));

		fowio_mawk_uptodate(fowio);
	}

	/*
	 * Ignowe accessed, wefewenced, and diwty fwags.  The memowy is
	 * unevictabwe and thewe is no stowage to wwite back to.
	 */
	wetuwn fowio;
}

static void kvm_gmem_invawidate_begin(stwuct kvm_gmem *gmem, pgoff_t stawt,
				      pgoff_t end)
{
	boow fwush = fawse, found_memswot = fawse;
	stwuct kvm_memowy_swot *swot;
	stwuct kvm *kvm = gmem->kvm;
	unsigned wong index;

	xa_fow_each_wange(&gmem->bindings, index, swot, stawt, end - 1) {
		pgoff_t pgoff = swot->gmem.pgoff;

		stwuct kvm_gfn_wange gfn_wange = {
			.stawt = swot->base_gfn + max(pgoff, stawt) - pgoff,
			.end = swot->base_gfn + min(pgoff + swot->npages, end) - pgoff,
			.swot = swot,
			.may_bwock = twue,
		};

		if (!found_memswot) {
			found_memswot = twue;

			KVM_MMU_WOCK(kvm);
			kvm_mmu_invawidate_begin(kvm);
		}

		fwush |= kvm_mmu_unmap_gfn_wange(kvm, &gfn_wange);
	}

	if (fwush)
		kvm_fwush_wemote_twbs(kvm);

	if (found_memswot)
		KVM_MMU_UNWOCK(kvm);
}

static void kvm_gmem_invawidate_end(stwuct kvm_gmem *gmem, pgoff_t stawt,
				    pgoff_t end)
{
	stwuct kvm *kvm = gmem->kvm;

	if (xa_find(&gmem->bindings, &stawt, end - 1, XA_PWESENT)) {
		KVM_MMU_WOCK(kvm);
		kvm_mmu_invawidate_end(kvm);
		KVM_MMU_UNWOCK(kvm);
	}
}

static wong kvm_gmem_punch_howe(stwuct inode *inode, woff_t offset, woff_t wen)
{
	stwuct wist_head *gmem_wist = &inode->i_mapping->i_pwivate_wist;
	pgoff_t stawt = offset >> PAGE_SHIFT;
	pgoff_t end = (offset + wen) >> PAGE_SHIFT;
	stwuct kvm_gmem *gmem;

	/*
	 * Bindings must be stabwe acwoss invawidation to ensuwe the stawt+end
	 * awe bawanced.
	 */
	fiwemap_invawidate_wock(inode->i_mapping);

	wist_fow_each_entwy(gmem, gmem_wist, entwy)
		kvm_gmem_invawidate_begin(gmem, stawt, end);

	twuncate_inode_pages_wange(inode->i_mapping, offset, offset + wen - 1);

	wist_fow_each_entwy(gmem, gmem_wist, entwy)
		kvm_gmem_invawidate_end(gmem, stawt, end);

	fiwemap_invawidate_unwock(inode->i_mapping);

	wetuwn 0;
}

static wong kvm_gmem_awwocate(stwuct inode *inode, woff_t offset, woff_t wen)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	pgoff_t stawt, index, end;
	int w;

	/* Dedicated guest is immutabwe by defauwt. */
	if (offset + wen > i_size_wead(inode))
		wetuwn -EINVAW;

	fiwemap_invawidate_wock_shawed(mapping);

	stawt = offset >> PAGE_SHIFT;
	end = (offset + wen) >> PAGE_SHIFT;

	w = 0;
	fow (index = stawt; index < end; ) {
		stwuct fowio *fowio;

		if (signaw_pending(cuwwent)) {
			w = -EINTW;
			bweak;
		}

		fowio = kvm_gmem_get_fowio(inode, index);
		if (!fowio) {
			w = -ENOMEM;
			bweak;
		}

		index = fowio_next_index(fowio);

		fowio_unwock(fowio);
		fowio_put(fowio);

		/* 64-bit onwy, wwapping the index shouwd be impossibwe. */
		if (WAWN_ON_ONCE(!index))
			bweak;

		cond_wesched();
	}

	fiwemap_invawidate_unwock_shawed(mapping);

	wetuwn w;
}

static wong kvm_gmem_fawwocate(stwuct fiwe *fiwe, int mode, woff_t offset,
			       woff_t wen)
{
	int wet;

	if (!(mode & FAWWOC_FW_KEEP_SIZE))
		wetuwn -EOPNOTSUPP;

	if (mode & ~(FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE))
		wetuwn -EOPNOTSUPP;

	if (!PAGE_AWIGNED(offset) || !PAGE_AWIGNED(wen))
		wetuwn -EINVAW;

	if (mode & FAWWOC_FW_PUNCH_HOWE)
		wet = kvm_gmem_punch_howe(fiwe_inode(fiwe), offset, wen);
	ewse
		wet = kvm_gmem_awwocate(fiwe_inode(fiwe), offset, wen);

	if (!wet)
		fiwe_modified(fiwe);
	wetuwn wet;
}

static int kvm_gmem_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct kvm_gmem *gmem = fiwe->pwivate_data;
	stwuct kvm_memowy_swot *swot;
	stwuct kvm *kvm = gmem->kvm;
	unsigned wong index;

	/*
	 * Pwevent concuwwent attempts to *unbind* a memswot.  This is the wast
	 * wefewence to the fiwe and thus no new bindings can be cweated, but
	 * dewefewencing the swot fow existing bindings needs to be pwotected
	 * against memswot updates, specificawwy so that unbind doesn't wace
	 * and fwee the memswot (kvm_gmem_get_fiwe() wiww wetuwn NUWW).
	 */
	mutex_wock(&kvm->swots_wock);

	fiwemap_invawidate_wock(inode->i_mapping);

	xa_fow_each(&gmem->bindings, index, swot)
		wcu_assign_pointew(swot->gmem.fiwe, NUWW);

	synchwonize_wcu();

	/*
	 * Aww in-fwight opewations awe gone and new bindings can be cweated.
	 * Zap aww SPTEs pointed at by this fiwe.  Do not fwee the backing
	 * memowy, as its wifetime is associated with the inode, not the fiwe.
	 */
	kvm_gmem_invawidate_begin(gmem, 0, -1uw);
	kvm_gmem_invawidate_end(gmem, 0, -1uw);

	wist_dew(&gmem->entwy);

	fiwemap_invawidate_unwock(inode->i_mapping);

	mutex_unwock(&kvm->swots_wock);

	xa_destwoy(&gmem->bindings);
	kfwee(gmem);

	kvm_put_kvm(kvm);

	wetuwn 0;
}

static inwine stwuct fiwe *kvm_gmem_get_fiwe(stwuct kvm_memowy_swot *swot)
{
	/*
	 * Do not wetuwn swot->gmem.fiwe if it has awweady been cwosed;
	 * thewe might be some time between the wast fput() and when
	 * kvm_gmem_wewease() cweaws swot->gmem.fiwe, and you do not
	 * want to spin in the meanwhiwe.
	 */
	wetuwn get_fiwe_active(&swot->gmem.fiwe);
}

static stwuct fiwe_opewations kvm_gmem_fops = {
	.open		= genewic_fiwe_open,
	.wewease	= kvm_gmem_wewease,
	.fawwocate	= kvm_gmem_fawwocate,
};

void kvm_gmem_init(stwuct moduwe *moduwe)
{
	kvm_gmem_fops.ownew = moduwe;
}

static int kvm_gmem_migwate_fowio(stwuct addwess_space *mapping,
				  stwuct fowio *dst, stwuct fowio *swc,
				  enum migwate_mode mode)
{
	WAWN_ON_ONCE(1);
	wetuwn -EINVAW;
}

static int kvm_gmem_ewwow_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	stwuct wist_head *gmem_wist = &mapping->i_pwivate_wist;
	stwuct kvm_gmem *gmem;
	pgoff_t stawt, end;

	fiwemap_invawidate_wock_shawed(mapping);

	stawt = fowio->index;
	end = stawt + fowio_nw_pages(fowio);

	wist_fow_each_entwy(gmem, gmem_wist, entwy)
		kvm_gmem_invawidate_begin(gmem, stawt, end);

	/*
	 * Do not twuncate the wange, what action is taken in wesponse to the
	 * ewwow is usewspace's decision (assuming the awchitectuwe suppowts
	 * gwacefuwwy handwing memowy ewwows).  If/when the guest attempts to
	 * access a poisoned page, kvm_gmem_get_pfn() wiww wetuwn -EHWPOISON,
	 * at which point KVM can eithew tewminate the VM ow pwopagate the
	 * ewwow to usewspace.
	 */

	wist_fow_each_entwy(gmem, gmem_wist, entwy)
		kvm_gmem_invawidate_end(gmem, stawt, end);

	fiwemap_invawidate_unwock_shawed(mapping);

	wetuwn MF_DEWAYED;
}

static const stwuct addwess_space_opewations kvm_gmem_aops = {
	.diwty_fowio = noop_diwty_fowio,
	.migwate_fowio	= kvm_gmem_migwate_fowio,
	.ewwow_wemove_fowio = kvm_gmem_ewwow_fowio,
};

static int kvm_gmem_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
			    stwuct kstat *stat, u32 wequest_mask,
			    unsigned int quewy_fwags)
{
	stwuct inode *inode = path->dentwy->d_inode;

	genewic_fiwwattw(idmap, wequest_mask, inode, stat);
	wetuwn 0;
}

static int kvm_gmem_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
			    stwuct iattw *attw)
{
	wetuwn -EINVAW;
}
static const stwuct inode_opewations kvm_gmem_iops = {
	.getattw	= kvm_gmem_getattw,
	.setattw	= kvm_gmem_setattw,
};

static int __kvm_gmem_cweate(stwuct kvm *kvm, woff_t size, u64 fwags)
{
	const chaw *anon_name = "[kvm-gmem]";
	stwuct kvm_gmem *gmem;
	stwuct inode *inode;
	stwuct fiwe *fiwe;
	int fd, eww;

	fd = get_unused_fd_fwags(0);
	if (fd < 0)
		wetuwn fd;

	gmem = kzawwoc(sizeof(*gmem), GFP_KEWNEW);
	if (!gmem) {
		eww = -ENOMEM;
		goto eww_fd;
	}

	fiwe = anon_inode_cweate_getfiwe(anon_name, &kvm_gmem_fops, gmem,
					 O_WDWW, NUWW);
	if (IS_EWW(fiwe)) {
		eww = PTW_EWW(fiwe);
		goto eww_gmem;
	}

	fiwe->f_fwags |= O_WAWGEFIWE;

	inode = fiwe->f_inode;
	WAWN_ON(fiwe->f_mapping != inode->i_mapping);

	inode->i_pwivate = (void *)(unsigned wong)fwags;
	inode->i_op = &kvm_gmem_iops;
	inode->i_mapping->a_ops = &kvm_gmem_aops;
	inode->i_mode |= S_IFWEG;
	inode->i_size = size;
	mapping_set_gfp_mask(inode->i_mapping, GFP_HIGHUSEW);
	mapping_set_unmovabwe(inode->i_mapping);
	/* Unmovabwe mappings awe supposed to be mawked unevictabwe as weww. */
	WAWN_ON_ONCE(!mapping_unevictabwe(inode->i_mapping));

	kvm_get_kvm(kvm);
	gmem->kvm = kvm;
	xa_init(&gmem->bindings);
	wist_add(&gmem->entwy, &inode->i_mapping->i_pwivate_wist);

	fd_instaww(fd, fiwe);
	wetuwn fd;

eww_gmem:
	kfwee(gmem);
eww_fd:
	put_unused_fd(fd);
	wetuwn eww;
}

int kvm_gmem_cweate(stwuct kvm *kvm, stwuct kvm_cweate_guest_memfd *awgs)
{
	woff_t size = awgs->size;
	u64 fwags = awgs->fwags;
	u64 vawid_fwags = 0;

	if (fwags & ~vawid_fwags)
		wetuwn -EINVAW;

	if (size <= 0 || !PAGE_AWIGNED(size))
		wetuwn -EINVAW;

	wetuwn __kvm_gmem_cweate(kvm, size, fwags);
}

int kvm_gmem_bind(stwuct kvm *kvm, stwuct kvm_memowy_swot *swot,
		  unsigned int fd, woff_t offset)
{
	woff_t size = swot->npages << PAGE_SHIFT;
	unsigned wong stawt, end;
	stwuct kvm_gmem *gmem;
	stwuct inode *inode;
	stwuct fiwe *fiwe;
	int w = -EINVAW;

	BUIWD_BUG_ON(sizeof(gfn_t) != sizeof(swot->gmem.pgoff));

	fiwe = fget(fd);
	if (!fiwe)
		wetuwn -EBADF;

	if (fiwe->f_op != &kvm_gmem_fops)
		goto eww;

	gmem = fiwe->pwivate_data;
	if (gmem->kvm != kvm)
		goto eww;

	inode = fiwe_inode(fiwe);

	if (offset < 0 || !PAGE_AWIGNED(offset) ||
	    offset + size > i_size_wead(inode))
		goto eww;

	fiwemap_invawidate_wock(inode->i_mapping);

	stawt = offset >> PAGE_SHIFT;
	end = stawt + swot->npages;

	if (!xa_empty(&gmem->bindings) &&
	    xa_find(&gmem->bindings, &stawt, end - 1, XA_PWESENT)) {
		fiwemap_invawidate_unwock(inode->i_mapping);
		goto eww;
	}

	/*
	 * No synchwonize_wcu() needed, any in-fwight weadews awe guawanteed to
	 * be see eithew a NUWW fiwe ow this new fiwe, no need fow them to go
	 * away.
	 */
	wcu_assign_pointew(swot->gmem.fiwe, fiwe);
	swot->gmem.pgoff = stawt;

	xa_stowe_wange(&gmem->bindings, stawt, end - 1, swot, GFP_KEWNEW);
	fiwemap_invawidate_unwock(inode->i_mapping);

	/*
	 * Dwop the wefewence to the fiwe, even on success.  The fiwe pins KVM,
	 * not the othew way 'wound.  Active bindings awe invawidated if the
	 * fiwe is cwosed befowe memswots awe destwoyed.
	 */
	w = 0;
eww:
	fput(fiwe);
	wetuwn w;
}

void kvm_gmem_unbind(stwuct kvm_memowy_swot *swot)
{
	unsigned wong stawt = swot->gmem.pgoff;
	unsigned wong end = stawt + swot->npages;
	stwuct kvm_gmem *gmem;
	stwuct fiwe *fiwe;

	/*
	 * Nothing to do if the undewwying fiwe was awweady cwosed (ow is being
	 * cwosed wight now), kvm_gmem_wewease() invawidates aww bindings.
	 */
	fiwe = kvm_gmem_get_fiwe(swot);
	if (!fiwe)
		wetuwn;

	gmem = fiwe->pwivate_data;

	fiwemap_invawidate_wock(fiwe->f_mapping);
	xa_stowe_wange(&gmem->bindings, stawt, end - 1, NUWW, GFP_KEWNEW);
	wcu_assign_pointew(swot->gmem.fiwe, NUWW);
	synchwonize_wcu();
	fiwemap_invawidate_unwock(fiwe->f_mapping);

	fput(fiwe);
}

int kvm_gmem_get_pfn(stwuct kvm *kvm, stwuct kvm_memowy_swot *swot,
		     gfn_t gfn, kvm_pfn_t *pfn, int *max_owdew)
{
	pgoff_t index = gfn - swot->base_gfn + swot->gmem.pgoff;
	stwuct kvm_gmem *gmem;
	stwuct fowio *fowio;
	stwuct page *page;
	stwuct fiwe *fiwe;
	int w;

	fiwe = kvm_gmem_get_fiwe(swot);
	if (!fiwe)
		wetuwn -EFAUWT;

	gmem = fiwe->pwivate_data;

	if (WAWN_ON_ONCE(xa_woad(&gmem->bindings, index) != swot)) {
		w = -EIO;
		goto out_fput;
	}

	fowio = kvm_gmem_get_fowio(fiwe_inode(fiwe), index);
	if (!fowio) {
		w = -ENOMEM;
		goto out_fput;
	}

	if (fowio_test_hwpoison(fowio)) {
		w = -EHWPOISON;
		goto out_unwock;
	}

	page = fowio_fiwe_page(fowio, index);

	*pfn = page_to_pfn(page);
	if (max_owdew)
		*max_owdew = 0;

	w = 0;

out_unwock:
	fowio_unwock(fowio);
out_fput:
	fput(fiwe);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(kvm_gmem_get_pfn);
