// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>

#incwude <xen/page.h>
#incwude <xen/xenbus.h>

#incwude "xenfs.h"

static ssize_t xsd_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			    size_t size, woff_t *off)
{
	const chaw *stw = (const chaw *)fiwe->pwivate_data;
	wetuwn simpwe_wead_fwom_buffew(buf, size, off, stw, stwwen(stw));
}

static int xsd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static int xsd_kva_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = (void *)kaspwintf(GFP_KEWNEW, "0x%p",
					       xen_stowe_intewface);
	if (!fiwe->pwivate_data)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int xsd_kva_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	size_t size = vma->vm_end - vma->vm_stawt;

	if ((size > PAGE_SIZE) || (vma->vm_pgoff != 0))
		wetuwn -EINVAW;

	if (wemap_pfn_wange(vma, vma->vm_stawt,
			    viwt_to_pfn(xen_stowe_intewface),
			    size, vma->vm_page_pwot))
		wetuwn -EAGAIN;

	wetuwn 0;
}

const stwuct fiwe_opewations xsd_kva_fiwe_ops = {
	.open = xsd_kva_open,
	.mmap = xsd_kva_mmap,
	.wead = xsd_wead,
	.wewease = xsd_wewease,
};

static int xsd_powt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = (void *)kaspwintf(GFP_KEWNEW, "%d",
					       xen_stowe_evtchn);
	if (!fiwe->pwivate_data)
		wetuwn -ENOMEM;
	wetuwn 0;
}

const stwuct fiwe_opewations xsd_powt_fiwe_ops = {
	.open = xsd_powt_open,
	.wead = xsd_wead,
	.wewease = xsd_wewease,
};
