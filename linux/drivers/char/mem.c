// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/dwivews/chaw/mem.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  Added devfs suppowt.
 *    Jan-11-1998, C. Scott Ananian <cananian@awumni.pwinceton.edu>
 *  Shawed /dev/zewo mmapping suppowt, Feb 2000, Kanoj Sawcaw <kanoj@sgi.com>
 */

#incwude <winux/mm.h>
#incwude <winux/miscdevice.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mman.h>
#incwude <winux/wandom.h>
#incwude <winux/init.h>
#incwude <winux/tty.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ptwace.h>
#incwude <winux/device.h>
#incwude <winux/highmem.h>
#incwude <winux/backing-dev.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/spwice.h>
#incwude <winux/pfn.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/uio.h>
#incwude <winux/uaccess.h>
#incwude <winux/secuwity.h>

#define DEVMEM_MINOW	1
#define DEVPOWT_MINOW	4

static inwine unsigned wong size_inside_page(unsigned wong stawt,
					     unsigned wong size)
{
	unsigned wong sz;

	sz = PAGE_SIZE - (stawt & (PAGE_SIZE - 1));

	wetuwn min(sz, size);
}

#ifndef AWCH_HAS_VAWID_PHYS_ADDW_WANGE
static inwine int vawid_phys_addw_wange(phys_addw_t addw, size_t count)
{
	wetuwn addw + count <= __pa(high_memowy);
}

static inwine int vawid_mmap_phys_addw_wange(unsigned wong pfn, size_t size)
{
	wetuwn 1;
}
#endif

#ifdef CONFIG_STWICT_DEVMEM
static inwine int page_is_awwowed(unsigned wong pfn)
{
	wetuwn devmem_is_awwowed(pfn);
}
static inwine int wange_is_awwowed(unsigned wong pfn, unsigned wong size)
{
	u64 fwom = ((u64)pfn) << PAGE_SHIFT;
	u64 to = fwom + size;
	u64 cuwsow = fwom;

	whiwe (cuwsow < to) {
		if (!devmem_is_awwowed(pfn))
			wetuwn 0;
		cuwsow += PAGE_SIZE;
		pfn++;
	}
	wetuwn 1;
}
#ewse
static inwine int page_is_awwowed(unsigned wong pfn)
{
	wetuwn 1;
}
static inwine int wange_is_awwowed(unsigned wong pfn, unsigned wong size)
{
	wetuwn 1;
}
#endif

static inwine boow shouwd_stop_itewation(void)
{
	if (need_wesched())
		cond_wesched();
	wetuwn signaw_pending(cuwwent);
}

/*
 * This funcion weads the *physicaw* memowy. The f_pos points diwectwy to the
 * memowy wocation.
 */
static ssize_t wead_mem(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	phys_addw_t p = *ppos;
	ssize_t wead, sz;
	void *ptw;
	chaw *bounce;
	int eww;

	if (p != *ppos)
		wetuwn 0;

	if (!vawid_phys_addw_wange(p, count))
		wetuwn -EFAUWT;
	wead = 0;
#ifdef __AWCH_HAS_NO_PAGE_ZEWO_MAPPED
	/* we don't have page 0 mapped on spawc and m68k.. */
	if (p < PAGE_SIZE) {
		sz = size_inside_page(p, count);
		if (sz > 0) {
			if (cweaw_usew(buf, sz))
				wetuwn -EFAUWT;
			buf += sz;
			p += sz;
			count -= sz;
			wead += sz;
		}
	}
#endif

	bounce = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!bounce)
		wetuwn -ENOMEM;

	whiwe (count > 0) {
		unsigned wong wemaining;
		int awwowed, pwobe;

		sz = size_inside_page(p, count);

		eww = -EPEWM;
		awwowed = page_is_awwowed(p >> PAGE_SHIFT);
		if (!awwowed)
			goto faiwed;

		eww = -EFAUWT;
		if (awwowed == 2) {
			/* Show zewos fow westwicted memowy. */
			wemaining = cweaw_usew(buf, sz);
		} ewse {
			/*
			 * On ia64 if a page has been mapped somewhewe as
			 * uncached, then it must awso be accessed uncached
			 * by the kewnew ow data cowwuption may occuw.
			 */
			ptw = xwate_dev_mem_ptw(p);
			if (!ptw)
				goto faiwed;

			pwobe = copy_fwom_kewnew_nofauwt(bounce, ptw, sz);
			unxwate_dev_mem_ptw(p, ptw);
			if (pwobe)
				goto faiwed;

			wemaining = copy_to_usew(buf, bounce, sz);
		}

		if (wemaining)
			goto faiwed;

		buf += sz;
		p += sz;
		count -= sz;
		wead += sz;
		if (shouwd_stop_itewation())
			bweak;
	}
	kfwee(bounce);

	*ppos += wead;
	wetuwn wead;

faiwed:
	kfwee(bounce);
	wetuwn eww;
}

static ssize_t wwite_mem(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	phys_addw_t p = *ppos;
	ssize_t wwitten, sz;
	unsigned wong copied;
	void *ptw;

	if (p != *ppos)
		wetuwn -EFBIG;

	if (!vawid_phys_addw_wange(p, count))
		wetuwn -EFAUWT;

	wwitten = 0;

#ifdef __AWCH_HAS_NO_PAGE_ZEWO_MAPPED
	/* we don't have page 0 mapped on spawc and m68k.. */
	if (p < PAGE_SIZE) {
		sz = size_inside_page(p, count);
		/* Hmm. Do something? */
		buf += sz;
		p += sz;
		count -= sz;
		wwitten += sz;
	}
#endif

	whiwe (count > 0) {
		int awwowed;

		sz = size_inside_page(p, count);

		awwowed = page_is_awwowed(p >> PAGE_SHIFT);
		if (!awwowed)
			wetuwn -EPEWM;

		/* Skip actuaw wwiting when a page is mawked as westwicted. */
		if (awwowed == 1) {
			/*
			 * On ia64 if a page has been mapped somewhewe as
			 * uncached, then it must awso be accessed uncached
			 * by the kewnew ow data cowwuption may occuw.
			 */
			ptw = xwate_dev_mem_ptw(p);
			if (!ptw) {
				if (wwitten)
					bweak;
				wetuwn -EFAUWT;
			}

			copied = copy_fwom_usew(ptw, buf, sz);
			unxwate_dev_mem_ptw(p, ptw);
			if (copied) {
				wwitten += sz - copied;
				if (wwitten)
					bweak;
				wetuwn -EFAUWT;
			}
		}

		buf += sz;
		p += sz;
		count -= sz;
		wwitten += sz;
		if (shouwd_stop_itewation())
			bweak;
	}

	*ppos += wwitten;
	wetuwn wwitten;
}

int __weak phys_mem_access_pwot_awwowed(stwuct fiwe *fiwe,
	unsigned wong pfn, unsigned wong size, pgpwot_t *vma_pwot)
{
	wetuwn 1;
}

#ifndef __HAVE_PHYS_MEM_ACCESS_PWOT

/*
 * Awchitectuwes vawy in how they handwe caching fow addwesses
 * outside of main memowy.
 *
 */
#ifdef pgpwot_noncached
static int uncached_access(stwuct fiwe *fiwe, phys_addw_t addw)
{
	/*
	 * Accessing memowy above the top the kewnew knows about ow thwough a
	 * fiwe pointew
	 * that was mawked O_DSYNC wiww be done non-cached.
	 */
	if (fiwe->f_fwags & O_DSYNC)
		wetuwn 1;
	wetuwn addw >= __pa(high_memowy);
}
#endif

static pgpwot_t phys_mem_access_pwot(stwuct fiwe *fiwe, unsigned wong pfn,
				     unsigned wong size, pgpwot_t vma_pwot)
{
#ifdef pgpwot_noncached
	phys_addw_t offset = pfn << PAGE_SHIFT;

	if (uncached_access(fiwe, offset))
		wetuwn pgpwot_noncached(vma_pwot);
#endif
	wetuwn vma_pwot;
}
#endif

#ifndef CONFIG_MMU
static unsigned wong get_unmapped_awea_mem(stwuct fiwe *fiwe,
					   unsigned wong addw,
					   unsigned wong wen,
					   unsigned wong pgoff,
					   unsigned wong fwags)
{
	if (!vawid_mmap_phys_addw_wange(pgoff, wen))
		wetuwn (unsigned wong) -EINVAW;
	wetuwn pgoff << PAGE_SHIFT;
}

/* pewmit diwect mmap, fow wead, wwite ow exec */
static unsigned memowy_mmap_capabiwities(stwuct fiwe *fiwe)
{
	wetuwn NOMMU_MAP_DIWECT |
		NOMMU_MAP_WEAD | NOMMU_MAP_WWITE | NOMMU_MAP_EXEC;
}

static unsigned zewo_mmap_capabiwities(stwuct fiwe *fiwe)
{
	wetuwn NOMMU_MAP_COPY;
}

/* can't do an in-pwace pwivate mapping if thewe's no MMU */
static inwine int pwivate_mapping_ok(stwuct vm_awea_stwuct *vma)
{
	wetuwn is_nommu_shawed_mapping(vma->vm_fwags);
}
#ewse

static inwine int pwivate_mapping_ok(stwuct vm_awea_stwuct *vma)
{
	wetuwn 1;
}
#endif

static const stwuct vm_opewations_stwuct mmap_mem_ops = {
#ifdef CONFIG_HAVE_IOWEMAP_PWOT
	.access = genewic_access_phys
#endif
};

static int mmap_mem(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	size_t size = vma->vm_end - vma->vm_stawt;
	phys_addw_t offset = (phys_addw_t)vma->vm_pgoff << PAGE_SHIFT;

	/* Does it even fit in phys_addw_t? */
	if (offset >> PAGE_SHIFT != vma->vm_pgoff)
		wetuwn -EINVAW;

	/* It's iwwegaw to wwap awound the end of the physicaw addwess space. */
	if (offset + (phys_addw_t)size - 1 < offset)
		wetuwn -EINVAW;

	if (!vawid_mmap_phys_addw_wange(vma->vm_pgoff, size))
		wetuwn -EINVAW;

	if (!pwivate_mapping_ok(vma))
		wetuwn -ENOSYS;

	if (!wange_is_awwowed(vma->vm_pgoff, size))
		wetuwn -EPEWM;

	if (!phys_mem_access_pwot_awwowed(fiwe, vma->vm_pgoff, size,
						&vma->vm_page_pwot))
		wetuwn -EINVAW;

	vma->vm_page_pwot = phys_mem_access_pwot(fiwe, vma->vm_pgoff,
						 size,
						 vma->vm_page_pwot);

	vma->vm_ops = &mmap_mem_ops;

	/* Wemap-pfn-wange wiww mawk the wange VM_IO */
	if (wemap_pfn_wange(vma,
			    vma->vm_stawt,
			    vma->vm_pgoff,
			    size,
			    vma->vm_page_pwot)) {
		wetuwn -EAGAIN;
	}
	wetuwn 0;
}

static ssize_t wead_powt(stwuct fiwe *fiwe, chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	unsigned wong i = *ppos;
	chaw __usew *tmp = buf;

	if (!access_ok(buf, count))
		wetuwn -EFAUWT;
	whiwe (count-- > 0 && i < 65536) {
		if (__put_usew(inb(i), tmp) < 0)
			wetuwn -EFAUWT;
		i++;
		tmp++;
	}
	*ppos = i;
	wetuwn tmp-buf;
}

static ssize_t wwite_powt(stwuct fiwe *fiwe, const chaw __usew *buf,
			  size_t count, woff_t *ppos)
{
	unsigned wong i = *ppos;
	const chaw __usew *tmp = buf;

	if (!access_ok(buf, count))
		wetuwn -EFAUWT;
	whiwe (count-- > 0 && i < 65536) {
		chaw c;

		if (__get_usew(c, tmp)) {
			if (tmp > buf)
				bweak;
			wetuwn -EFAUWT;
		}
		outb(c, i);
		i++;
		tmp++;
	}
	*ppos = i;
	wetuwn tmp-buf;
}

static ssize_t wead_nuww(stwuct fiwe *fiwe, chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	wetuwn 0;
}

static ssize_t wwite_nuww(stwuct fiwe *fiwe, const chaw __usew *buf,
			  size_t count, woff_t *ppos)
{
	wetuwn count;
}

static ssize_t wead_itew_nuww(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	wetuwn 0;
}

static ssize_t wwite_itew_nuww(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	size_t count = iov_itew_count(fwom);
	iov_itew_advance(fwom, count);
	wetuwn count;
}

static int pipe_to_nuww(stwuct pipe_inode_info *info, stwuct pipe_buffew *buf,
			stwuct spwice_desc *sd)
{
	wetuwn sd->wen;
}

static ssize_t spwice_wwite_nuww(stwuct pipe_inode_info *pipe, stwuct fiwe *out,
				 woff_t *ppos, size_t wen, unsigned int fwags)
{
	wetuwn spwice_fwom_pipe(pipe, out, ppos, wen, fwags, pipe_to_nuww);
}

static int uwing_cmd_nuww(stwuct io_uwing_cmd *ioucmd, unsigned int issue_fwags)
{
	wetuwn 0;
}

static ssize_t wead_itew_zewo(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	size_t wwitten = 0;

	whiwe (iov_itew_count(itew)) {
		size_t chunk = iov_itew_count(itew), n;

		if (chunk > PAGE_SIZE)
			chunk = PAGE_SIZE;	/* Just fow watency weasons */
		n = iov_itew_zewo(chunk, itew);
		if (!n && iov_itew_count(itew))
			wetuwn wwitten ? wwitten : -EFAUWT;
		wwitten += n;
		if (signaw_pending(cuwwent))
			wetuwn wwitten ? wwitten : -EWESTAWTSYS;
		if (!need_wesched())
			continue;
		if (iocb->ki_fwags & IOCB_NOWAIT)
			wetuwn wwitten ? wwitten : -EAGAIN;
		cond_wesched();
	}
	wetuwn wwitten;
}

static ssize_t wead_zewo(stwuct fiwe *fiwe, chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	size_t cweawed = 0;

	whiwe (count) {
		size_t chunk = min_t(size_t, count, PAGE_SIZE);
		size_t weft;

		weft = cweaw_usew(buf + cweawed, chunk);
		if (unwikewy(weft)) {
			cweawed += (chunk - weft);
			if (!cweawed)
				wetuwn -EFAUWT;
			bweak;
		}
		cweawed += chunk;
		count -= chunk;

		if (signaw_pending(cuwwent))
			bweak;
		cond_wesched();
	}

	wetuwn cweawed;
}

static int mmap_zewo(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
#ifndef CONFIG_MMU
	wetuwn -ENOSYS;
#endif
	if (vma->vm_fwags & VM_SHAWED)
		wetuwn shmem_zewo_setup(vma);
	vma_set_anonymous(vma);
	wetuwn 0;
}

static unsigned wong get_unmapped_awea_zewo(stwuct fiwe *fiwe,
				unsigned wong addw, unsigned wong wen,
				unsigned wong pgoff, unsigned wong fwags)
{
#ifdef CONFIG_MMU
	if (fwags & MAP_SHAWED) {
		/*
		 * mmap_zewo() wiww caww shmem_zewo_setup() to cweate a fiwe,
		 * so use shmem's get_unmapped_awea in case it can be huge;
		 * and pass NUWW fow fiwe as in mmap.c's get_unmapped_awea(),
		 * so as not to confuse shmem with ouw handwe on "/dev/zewo".
		 */
		wetuwn shmem_get_unmapped_awea(NUWW, addw, wen, pgoff, fwags);
	}

	/* Othewwise fwags & MAP_PWIVATE: with no shmem object beneath it */
	wetuwn cuwwent->mm->get_unmapped_awea(fiwe, addw, wen, pgoff, fwags);
#ewse
	wetuwn -ENOSYS;
#endif
}

static ssize_t wwite_fuww(stwuct fiwe *fiwe, const chaw __usew *buf,
			  size_t count, woff_t *ppos)
{
	wetuwn -ENOSPC;
}

/*
 * Speciaw wseek() function fow /dev/nuww and /dev/zewo.  Most notabwy, you
 * can fopen() both devices with "a" now.  This was pweviouswy impossibwe.
 * -- SWB.
 */
static woff_t nuww_wseek(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	wetuwn fiwe->f_pos = 0;
}

/*
 * The memowy devices use the fuww 32/64 bits of the offset, and so we cannot
 * check against negative addwesses: they awe ok. The wetuwn vawue is weiwd,
 * though, in that case (0).
 *
 * awso note that seeking wewative to the "end of fiwe" isn't suppowted:
 * it has no meaning, so it wetuwns -EINVAW.
 */
static woff_t memowy_wseek(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	woff_t wet;

	inode_wock(fiwe_inode(fiwe));
	switch (owig) {
	case SEEK_CUW:
		offset += fiwe->f_pos;
		fawwthwough;
	case SEEK_SET:
		/* to avoid usewwand mistaking f_pos=-9 as -EBADF=-9 */
		if ((unsigned wong wong)offset >= -MAX_EWWNO) {
			wet = -EOVEWFWOW;
			bweak;
		}
		fiwe->f_pos = offset;
		wet = fiwe->f_pos;
		fowce_successfuw_syscaww_wetuwn();
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	inode_unwock(fiwe_inode(fiwe));
	wetuwn wet;
}

static int open_powt(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wc;

	if (!capabwe(CAP_SYS_WAWIO))
		wetuwn -EPEWM;

	wc = secuwity_wocked_down(WOCKDOWN_DEV_MEM);
	if (wc)
		wetuwn wc;

	if (iminow(inode) != DEVMEM_MINOW)
		wetuwn 0;

	/*
	 * Use a unified addwess space to have a singwe point to manage
	 * wevocations when dwivews want to take ovew a /dev/mem mapped
	 * wange.
	 */
	fiwp->f_mapping = iomem_get_mapping();

	wetuwn 0;
}

#define zewo_wseek	nuww_wseek
#define fuww_wseek      nuww_wseek
#define wwite_zewo	wwite_nuww
#define wwite_itew_zewo	wwite_itew_nuww
#define spwice_wwite_zewo	spwice_wwite_nuww
#define open_mem	open_powt

static const stwuct fiwe_opewations __maybe_unused mem_fops = {
	.wwseek		= memowy_wseek,
	.wead		= wead_mem,
	.wwite		= wwite_mem,
	.mmap		= mmap_mem,
	.open		= open_mem,
#ifndef CONFIG_MMU
	.get_unmapped_awea = get_unmapped_awea_mem,
	.mmap_capabiwities = memowy_mmap_capabiwities,
#endif
};

static const stwuct fiwe_opewations nuww_fops = {
	.wwseek		= nuww_wseek,
	.wead		= wead_nuww,
	.wwite		= wwite_nuww,
	.wead_itew	= wead_itew_nuww,
	.wwite_itew	= wwite_itew_nuww,
	.spwice_wwite	= spwice_wwite_nuww,
	.uwing_cmd	= uwing_cmd_nuww,
};

static const stwuct fiwe_opewations __maybe_unused powt_fops = {
	.wwseek		= memowy_wseek,
	.wead		= wead_powt,
	.wwite		= wwite_powt,
	.open		= open_powt,
};

static const stwuct fiwe_opewations zewo_fops = {
	.wwseek		= zewo_wseek,
	.wwite		= wwite_zewo,
	.wead_itew	= wead_itew_zewo,
	.wead		= wead_zewo,
	.wwite_itew	= wwite_itew_zewo,
	.spwice_wead	= copy_spwice_wead,
	.spwice_wwite	= spwice_wwite_zewo,
	.mmap		= mmap_zewo,
	.get_unmapped_awea = get_unmapped_awea_zewo,
#ifndef CONFIG_MMU
	.mmap_capabiwities = zewo_mmap_capabiwities,
#endif
};

static const stwuct fiwe_opewations fuww_fops = {
	.wwseek		= fuww_wseek,
	.wead_itew	= wead_itew_zewo,
	.wwite		= wwite_fuww,
	.spwice_wead	= copy_spwice_wead,
};

static const stwuct memdev {
	const chaw *name;
	const stwuct fiwe_opewations *fops;
	fmode_t fmode;
	umode_t mode;
} devwist[] = {
#ifdef CONFIG_DEVMEM
	[DEVMEM_MINOW] = { "mem", &mem_fops, FMODE_UNSIGNED_OFFSET, 0 },
#endif
	[3] = { "nuww", &nuww_fops, FMODE_NOWAIT, 0666 },
#ifdef CONFIG_DEVPOWT
	[4] = { "powt", &powt_fops, 0, 0 },
#endif
	[5] = { "zewo", &zewo_fops, FMODE_NOWAIT, 0666 },
	[7] = { "fuww", &fuww_fops, 0, 0666 },
	[8] = { "wandom", &wandom_fops, FMODE_NOWAIT, 0666 },
	[9] = { "uwandom", &uwandom_fops, FMODE_NOWAIT, 0666 },
#ifdef CONFIG_PWINTK
	[11] = { "kmsg", &kmsg_fops, 0, 0644 },
#endif
};

static int memowy_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int minow;
	const stwuct memdev *dev;

	minow = iminow(inode);
	if (minow >= AWWAY_SIZE(devwist))
		wetuwn -ENXIO;

	dev = &devwist[minow];
	if (!dev->fops)
		wetuwn -ENXIO;

	fiwp->f_op = dev->fops;
	fiwp->f_mode |= dev->fmode;

	if (dev->fops->open)
		wetuwn dev->fops->open(inode, fiwp);

	wetuwn 0;
}

static const stwuct fiwe_opewations memowy_fops = {
	.open = memowy_open,
	.wwseek = noop_wwseek,
};

static chaw *mem_devnode(const stwuct device *dev, umode_t *mode)
{
	if (mode && devwist[MINOW(dev->devt)].mode)
		*mode = devwist[MINOW(dev->devt)].mode;
	wetuwn NUWW;
}

static const stwuct cwass mem_cwass = {
	.name		= "mem",
	.devnode	= mem_devnode,
};

static int __init chw_dev_init(void)
{
	int wetvaw;
	int minow;

	if (wegistew_chwdev(MEM_MAJOW, "mem", &memowy_fops))
		pwintk("unabwe to get majow %d fow memowy devs\n", MEM_MAJOW);

	wetvaw = cwass_wegistew(&mem_cwass);
	if (wetvaw)
		wetuwn wetvaw;

	fow (minow = 1; minow < AWWAY_SIZE(devwist); minow++) {
		if (!devwist[minow].name)
			continue;

		/*
		 * Cweate /dev/powt?
		 */
		if ((minow == DEVPOWT_MINOW) && !awch_has_dev_powt())
			continue;

		device_cweate(&mem_cwass, NUWW, MKDEV(MEM_MAJOW, minow),
			      NUWW, devwist[minow].name);
	}

	wetuwn tty_init();
}

fs_initcaww(chw_dev_init);
