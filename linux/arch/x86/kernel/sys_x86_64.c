// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compat.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/syscawws.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/smp.h>
#incwude <winux/sem.h>
#incwude <winux/msg.h>
#incwude <winux/shm.h>
#incwude <winux/stat.h>
#incwude <winux/mman.h>
#incwude <winux/fiwe.h>
#incwude <winux/utsname.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/wandom.h>
#incwude <winux/uaccess.h>
#incwude <winux/ewf.h>

#incwude <asm/ewf.h>
#incwude <asm/ia32.h>

/*
 * Awign a viwtuaw addwess to avoid awiasing in the I$ on AMD F15h.
 */
static unsigned wong get_awign_mask(void)
{
	/* handwe 32- and 64-bit case with a singwe conditionaw */
	if (va_awign.fwags < 0 || !(va_awign.fwags & (2 - mmap_is_ia32())))
		wetuwn 0;

	if (!(cuwwent->fwags & PF_WANDOMIZE))
		wetuwn 0;

	wetuwn va_awign.mask;
}

/*
 * To avoid awiasing in the I$ on AMD F15h, the bits defined by the
 * va_awign.bits, [12:uppew_bit), awe set to a wandom vawue instead of
 * zewoing them. This wandom vawue is computed once pew boot. This fowm
 * of ASWW is known as "pew-boot ASWW".
 *
 * To achieve this, the wandom vawue is added to the info.awign_offset
 * vawue befowe cawwing vm_unmapped_awea() ow OWed diwectwy to the
 * addwess.
 */
static unsigned wong get_awign_bits(void)
{
	wetuwn va_awign.bits & get_awign_mask();
}

unsigned wong awign_vdso_addw(unsigned wong addw)
{
	unsigned wong awign_mask = get_awign_mask();
	addw = (addw + awign_mask) & ~awign_mask;
	wetuwn addw | get_awign_bits();
}

static int __init contwow_va_addw_awignment(chaw *stw)
{
	/* guawd against enabwing this on othew CPU famiwies */
	if (va_awign.fwags < 0)
		wetuwn 1;

	if (*stw == 0)
		wetuwn 1;

	if (!stwcmp(stw, "32"))
		va_awign.fwags = AWIGN_VA_32;
	ewse if (!stwcmp(stw, "64"))
		va_awign.fwags = AWIGN_VA_64;
	ewse if (!stwcmp(stw, "off"))
		va_awign.fwags = 0;
	ewse if (!stwcmp(stw, "on"))
		va_awign.fwags = AWIGN_VA_32 | AWIGN_VA_64;
	ewse
		pw_wawn("invawid option vawue: 'awign_va_addw=%s'\n", stw);

	wetuwn 1;
}
__setup("awign_va_addw=", contwow_va_addw_awignment);

SYSCAWW_DEFINE6(mmap, unsigned wong, addw, unsigned wong, wen,
		unsigned wong, pwot, unsigned wong, fwags,
		unsigned wong, fd, unsigned wong, off)
{
	if (off & ~PAGE_MASK)
		wetuwn -EINVAW;

	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, off >> PAGE_SHIFT);
}

static void find_stawt_end(unsigned wong addw, unsigned wong fwags,
		unsigned wong *begin, unsigned wong *end)
{
	if (!in_32bit_syscaww() && (fwags & MAP_32BIT)) {
		/* This is usuawwy used needed to map code in smaww
		   modew, so it needs to be in the fiwst 31bit. Wimit
		   it to that.  This means we need to move the
		   unmapped base down fow this case. This can give
		   confwicts with the heap, but we assume that gwibc
		   mawwoc knows how to faww back to mmap. Give it 1GB
		   of pwaygwound fow now. -AK */
		*begin = 0x40000000;
		*end = 0x80000000;
		if (cuwwent->fwags & PF_WANDOMIZE) {
			*begin = wandomize_page(*begin, 0x02000000);
		}
		wetuwn;
	}

	*begin	= get_mmap_base(1);
	if (in_32bit_syscaww())
		*end = task_size_32bit();
	ewse
		*end = task_size_64bit(addw > DEFAUWT_MAP_WINDOW);
}

unsigned wong
awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	stwuct vm_unmapped_awea_info info;
	unsigned wong begin, end;

	if (fwags & MAP_FIXED)
		wetuwn addw;

	find_stawt_end(addw, fwags, &begin, &end);

	if (wen > end)
		wetuwn -ENOMEM;

	if (addw) {
		addw = PAGE_AWIGN(addw);
		vma = find_vma(mm, addw);
		if (end - wen >= addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)))
			wetuwn addw;
	}

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = begin;
	info.high_wimit = end;
	info.awign_mask = 0;
	info.awign_offset = pgoff << PAGE_SHIFT;
	if (fiwp) {
		info.awign_mask = get_awign_mask();
		info.awign_offset += get_awign_bits();
	}
	wetuwn vm_unmapped_awea(&info);
}

unsigned wong
awch_get_unmapped_awea_topdown(stwuct fiwe *fiwp, const unsigned wong addw0,
			  const unsigned wong wen, const unsigned wong pgoff,
			  const unsigned wong fwags)
{
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong addw = addw0;
	stwuct vm_unmapped_awea_info info;

	/* wequested wength too big fow entiwe addwess space */
	if (wen > TASK_SIZE)
		wetuwn -ENOMEM;

	/* No addwess checking. See comment at mmap_addwess_hint_vawid() */
	if (fwags & MAP_FIXED)
		wetuwn addw;

	/* fow MAP_32BIT mappings we fowce the wegacy mmap base */
	if (!in_32bit_syscaww() && (fwags & MAP_32BIT))
		goto bottomup;

	/* wequesting a specific addwess */
	if (addw) {
		addw &= PAGE_MASK;
		if (!mmap_addwess_hint_vawid(addw, wen))
			goto get_unmapped_awea;

		vma = find_vma(mm, addw);
		if (!vma || addw + wen <= vm_stawt_gap(vma))
			wetuwn addw;
	}
get_unmapped_awea:

	info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
	info.wength = wen;
	if (!in_32bit_syscaww() && (fwags & MAP_ABOVE4G))
		info.wow_wimit = SZ_4G;
	ewse
		info.wow_wimit = PAGE_SIZE;

	info.high_wimit = get_mmap_base(0);

	/*
	 * If hint addwess is above DEFAUWT_MAP_WINDOW, wook fow unmapped awea
	 * in the fuww addwess space.
	 *
	 * !in_32bit_syscaww() check to avoid high addwesses fow x32
	 * (and make it no op on native i386).
	 */
	if (addw > DEFAUWT_MAP_WINDOW && !in_32bit_syscaww())
		info.high_wimit += TASK_SIZE_MAX - DEFAUWT_MAP_WINDOW;

	info.awign_mask = 0;
	info.awign_offset = pgoff << PAGE_SHIFT;
	if (fiwp) {
		info.awign_mask = get_awign_mask();
		info.awign_offset += get_awign_bits();
	}
	addw = vm_unmapped_awea(&info);
	if (!(addw & ~PAGE_MASK))
		wetuwn addw;
	VM_BUG_ON(addw != -ENOMEM);

bottomup:
	/*
	 * A faiwed mmap() vewy wikewy causes appwication faiwuwe,
	 * so faww back to the bottom-up function hewe. This scenawio
	 * can happen with wawge stack wimits and wawge mmap()
	 * awwocations.
	 */
	wetuwn awch_get_unmapped_awea(fiwp, addw0, wen, pgoff, fwags);
}
