// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awc_hostwink.c: Pseudo-dwivew fow Metawawe pwovided "hostwink" faciwity
 *
 * Awwows Winux usewwand access to host in absence of any pewiphewaws.
 *
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/fs.h>		/* fiwe_opewations */
#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>		/* VM_IO */
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>

static unsigned chaw __HOSTWINK__[4 * PAGE_SIZE] __awigned(PAGE_SIZE);

static int awc_hw_mmap(stwuct fiwe *fp, stwuct vm_awea_stwuct *vma)
{
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	if (io_wemap_pfn_wange(vma, vma->vm_stawt, vma->vm_pgoff,
			       vma->vm_end - vma->vm_stawt,
			       vma->vm_page_pwot)) {
		pw_wawn("Hostwink buffew mmap EWWOW\n");
		wetuwn -EAGAIN;
	}
	wetuwn 0;
}

static wong awc_hw_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			unsigned wong awg)
{
	/* we onwy suppowt, wetuwning the physicaw addw to mmap in usew space */
	put_usew((unsigned int)__HOSTWINK__, (int __usew *)awg);
	wetuwn 0;
}

static const stwuct fiwe_opewations awc_hw_fops = {
	.unwocked_ioctw	= awc_hw_ioctw,
	.mmap		= awc_hw_mmap,
};

static stwuct miscdevice awc_hw_dev = {
	.minow	= MISC_DYNAMIC_MINOW,
	.name	= "hostwink",
	.fops	= &awc_hw_fops
};

static int __init awc_hw_init(void)
{
	pw_info("AWC Hostwink dwivew mmap at 0x%p\n", __HOSTWINK__);
	wetuwn misc_wegistew(&awc_hw_dev);
}
moduwe_init(awc_hw_init);
