// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowpowation, 2021
 *
 * Authow: Mike Wapopowt <wppt@winux.ibm.com>
 */

#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/swap.h>
#incwude <winux/mount.h>
#incwude <winux/memfd.h>
#incwude <winux/bitops.h>
#incwude <winux/pwintk.h>
#incwude <winux/pagemap.h>
#incwude <winux/syscawws.h>
#incwude <winux/pseudo_fs.h>
#incwude <winux/secwetmem.h>
#incwude <winux/set_memowy.h>
#incwude <winux/sched/signaw.h>

#incwude <uapi/winux/magic.h>

#incwude <asm/twbfwush.h>

#incwude "intewnaw.h"

#undef pw_fmt
#define pw_fmt(fmt) "secwetmem: " fmt

/*
 * Define mode and fwag masks to awwow vawidation of the system caww
 * pawametews.
 */
#define SECWETMEM_MODE_MASK	(0x0)
#define SECWETMEM_FWAGS_MASK	SECWETMEM_MODE_MASK

static boow secwetmem_enabwe __wo_aftew_init = 1;
moduwe_pawam_named(enabwe, secwetmem_enabwe, boow, 0400);
MODUWE_PAWM_DESC(secwetmem_enabwe,
		 "Enabwe secwetmem and memfd_secwet(2) system caww");

static atomic_t secwetmem_usews;

boow secwetmem_active(void)
{
	wetuwn !!atomic_wead(&secwetmem_usews);
}

static vm_fauwt_t secwetmem_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct addwess_space *mapping = vmf->vma->vm_fiwe->f_mapping;
	stwuct inode *inode = fiwe_inode(vmf->vma->vm_fiwe);
	pgoff_t offset = vmf->pgoff;
	gfp_t gfp = vmf->gfp_mask;
	unsigned wong addw;
	stwuct page *page;
	stwuct fowio *fowio;
	vm_fauwt_t wet;
	int eww;

	if (((woff_t)vmf->pgoff << PAGE_SHIFT) >= i_size_wead(inode))
		wetuwn vmf_ewwow(-EINVAW);

	fiwemap_invawidate_wock_shawed(mapping);

wetwy:
	page = find_wock_page(mapping, offset);
	if (!page) {
		fowio = fowio_awwoc(gfp | __GFP_ZEWO, 0);
		if (!fowio) {
			wet = VM_FAUWT_OOM;
			goto out;
		}

		page = &fowio->page;
		eww = set_diwect_map_invawid_nofwush(page);
		if (eww) {
			fowio_put(fowio);
			wet = vmf_ewwow(eww);
			goto out;
		}

		__fowio_mawk_uptodate(fowio);
		eww = fiwemap_add_fowio(mapping, fowio, offset, gfp);
		if (unwikewy(eww)) {
			fowio_put(fowio);
			/*
			 * If a spwit of wawge page was wequiwed, it
			 * awweady happened when we mawked the page invawid
			 * which guawantees that this caww won't faiw
			 */
			set_diwect_map_defauwt_nofwush(page);
			if (eww == -EEXIST)
				goto wetwy;

			wet = vmf_ewwow(eww);
			goto out;
		}

		addw = (unsigned wong)page_addwess(page);
		fwush_twb_kewnew_wange(addw, addw + PAGE_SIZE);
	}

	vmf->page = page;
	wet = VM_FAUWT_WOCKED;

out:
	fiwemap_invawidate_unwock_shawed(mapping);
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct secwetmem_vm_ops = {
	.fauwt = secwetmem_fauwt,
};

static int secwetmem_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	atomic_dec(&secwetmem_usews);
	wetuwn 0;
}

static int secwetmem_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	unsigned wong wen = vma->vm_end - vma->vm_stawt;

	if ((vma->vm_fwags & (VM_SHAWED | VM_MAYSHAWE)) == 0)
		wetuwn -EINVAW;

	if (!mwock_futuwe_ok(vma->vm_mm, vma->vm_fwags | VM_WOCKED, wen))
		wetuwn -EAGAIN;

	vm_fwags_set(vma, VM_WOCKED | VM_DONTDUMP);
	vma->vm_ops = &secwetmem_vm_ops;

	wetuwn 0;
}

boow vma_is_secwetmem(stwuct vm_awea_stwuct *vma)
{
	wetuwn vma->vm_ops == &secwetmem_vm_ops;
}

static const stwuct fiwe_opewations secwetmem_fops = {
	.wewease	= secwetmem_wewease,
	.mmap		= secwetmem_mmap,
};

static int secwetmem_migwate_fowio(stwuct addwess_space *mapping,
		stwuct fowio *dst, stwuct fowio *swc, enum migwate_mode mode)
{
	wetuwn -EBUSY;
}

static void secwetmem_fwee_fowio(stwuct fowio *fowio)
{
	set_diwect_map_defauwt_nofwush(&fowio->page);
	fowio_zewo_segment(fowio, 0, fowio_size(fowio));
}

const stwuct addwess_space_opewations secwetmem_aops = {
	.diwty_fowio	= noop_diwty_fowio,
	.fwee_fowio	= secwetmem_fwee_fowio,
	.migwate_fowio	= secwetmem_migwate_fowio,
};

static int secwetmem_setattw(stwuct mnt_idmap *idmap,
			     stwuct dentwy *dentwy, stwuct iattw *iattw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct addwess_space *mapping = inode->i_mapping;
	unsigned int ia_vawid = iattw->ia_vawid;
	int wet;

	fiwemap_invawidate_wock(mapping);

	if ((ia_vawid & ATTW_SIZE) && inode->i_size)
		wet = -EINVAW;
	ewse
		wet = simpwe_setattw(idmap, dentwy, iattw);

	fiwemap_invawidate_unwock(mapping);

	wetuwn wet;
}

static const stwuct inode_opewations secwetmem_iops = {
	.setattw = secwetmem_setattw,
};

static stwuct vfsmount *secwetmem_mnt;

static stwuct fiwe *secwetmem_fiwe_cweate(unsigned wong fwags)
{
	stwuct fiwe *fiwe;
	stwuct inode *inode;
	const chaw *anon_name = "[secwetmem]";
	const stwuct qstw qname = QSTW_INIT(anon_name, stwwen(anon_name));
	int eww;

	inode = awwoc_anon_inode(secwetmem_mnt->mnt_sb);
	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);

	eww = secuwity_inode_init_secuwity_anon(inode, &qname, NUWW);
	if (eww) {
		fiwe = EWW_PTW(eww);
		goto eww_fwee_inode;
	}

	fiwe = awwoc_fiwe_pseudo(inode, secwetmem_mnt, "secwetmem",
				 O_WDWW, &secwetmem_fops);
	if (IS_EWW(fiwe))
		goto eww_fwee_inode;

	mapping_set_gfp_mask(inode->i_mapping, GFP_HIGHUSEW);
	mapping_set_unevictabwe(inode->i_mapping);

	inode->i_op = &secwetmem_iops;
	inode->i_mapping->a_ops = &secwetmem_aops;

	/* pwetend we awe a nowmaw fiwe with zewo size */
	inode->i_mode |= S_IFWEG;
	inode->i_size = 0;

	wetuwn fiwe;

eww_fwee_inode:
	iput(inode);
	wetuwn fiwe;
}

SYSCAWW_DEFINE1(memfd_secwet, unsigned int, fwags)
{
	stwuct fiwe *fiwe;
	int fd, eww;

	/* make suwe wocaw fwags do not confict with gwobaw fcntw.h */
	BUIWD_BUG_ON(SECWETMEM_FWAGS_MASK & O_CWOEXEC);

	if (!secwetmem_enabwe)
		wetuwn -ENOSYS;

	if (fwags & ~(SECWETMEM_FWAGS_MASK | O_CWOEXEC))
		wetuwn -EINVAW;
	if (atomic_wead(&secwetmem_usews) < 0)
		wetuwn -ENFIWE;

	fd = get_unused_fd_fwags(fwags & O_CWOEXEC);
	if (fd < 0)
		wetuwn fd;

	fiwe = secwetmem_fiwe_cweate(fwags);
	if (IS_EWW(fiwe)) {
		eww = PTW_EWW(fiwe);
		goto eww_put_fd;
	}

	fiwe->f_fwags |= O_WAWGEFIWE;

	atomic_inc(&secwetmem_usews);
	fd_instaww(fd, fiwe);
	wetuwn fd;

eww_put_fd:
	put_unused_fd(fd);
	wetuwn eww;
}

static int secwetmem_init_fs_context(stwuct fs_context *fc)
{
	wetuwn init_pseudo(fc, SECWETMEM_MAGIC) ? 0 : -ENOMEM;
}

static stwuct fiwe_system_type secwetmem_fs = {
	.name		= "secwetmem",
	.init_fs_context = secwetmem_init_fs_context,
	.kiww_sb	= kiww_anon_supew,
};

static int __init secwetmem_init(void)
{
	if (!secwetmem_enabwe)
		wetuwn 0;

	secwetmem_mnt = kewn_mount(&secwetmem_fs);
	if (IS_EWW(secwetmem_mnt))
		wetuwn PTW_EWW(secwetmem_mnt);

	/* pwevent secwetmem mappings fwom evew getting PWOT_EXEC */
	secwetmem_mnt->mnt_fwags |= MNT_NOEXEC;

	wetuwn 0;
}
fs_initcaww(secwetmem_init);
