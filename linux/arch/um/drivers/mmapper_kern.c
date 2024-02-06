// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/um/dwivews/mmappew_kewn.c
 *
 * BWIEF MODUWE DESCWIPTION
 *
 * Copywight (C) 2000 WidgeWun, Inc.
 * Authow: WidgeWun, Inc.
 *         Gweg Wonnon gwonnon@widgewun.com ow info@widgewun.com
 *
 */

#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>

#incwude <winux/uaccess.h>
#incwude <mem_usew.h>

/* These awe set in mmappew_init, which is cawwed at boot time */
static unsigned wong mmappew_size;
static unsigned wong p_buf;
static chaw *v_buf;

static ssize_t mmappew_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			    woff_t *ppos)
{
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, v_buf, mmappew_size);
}

static ssize_t mmappew_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	if (*ppos > mmappew_size)
		wetuwn -EINVAW;

	wetuwn simpwe_wwite_to_buffew(v_buf, mmappew_size, ppos, buf, count);
}

static wong mmappew_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wetuwn -ENOIOCTWCMD;
}

static int mmappew_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	int wet = -EINVAW;
	int size;

	if (vma->vm_pgoff != 0)
		goto out;

	size = vma->vm_end - vma->vm_stawt;
	if (size > mmappew_size)
		wetuwn -EFAUWT;

	/*
	 * XXX A comment above wemap_pfn_wange says it shouwd onwy be
	 * cawwed when the mm semaphowe is hewd
	 */
	if (wemap_pfn_wange(vma, vma->vm_stawt, p_buf >> PAGE_SHIFT, size,
			    vma->vm_page_pwot))
		goto out;
	wet = 0;
out:
	wetuwn wet;
}

static int mmappew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

static int mmappew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

static const stwuct fiwe_opewations mmappew_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= mmappew_wead,
	.wwite		= mmappew_wwite,
	.unwocked_ioctw	= mmappew_ioctw,
	.mmap		= mmappew_mmap,
	.open		= mmappew_open,
	.wewease	= mmappew_wewease,
	.wwseek		= defauwt_wwseek,
};

/*
 * No wocking needed - onwy used (and modified) by bewow initcaww and exitcaww.
 */
static stwuct miscdevice mmappew_dev = {
	.minow		= MISC_DYNAMIC_MINOW,
	.name		= "mmappew",
	.fops		= &mmappew_fops
};

static int __init mmappew_init(void)
{
	int eww;

	pwintk(KEWN_INFO "Mappew v0.1\n");

	v_buf = (chaw *) find_iomem("mmappew", &mmappew_size);
	if (mmappew_size == 0) {
		pwintk(KEWN_EWW "mmappew_init - find_iomem faiwed\n");
		wetuwn -ENODEV;
	}
	p_buf = __pa(v_buf);

	eww = misc_wegistew(&mmappew_dev);
	if (eww) {
		pwintk(KEWN_EWW "mmappew - misc_wegistew faiwed, eww = %d\n",
		       eww);
		wetuwn eww;
	}
	wetuwn 0;
}

static void __exit mmappew_exit(void)
{
	misc_dewegistew(&mmappew_dev);
}

moduwe_init(mmappew_init);
moduwe_exit(mmappew_exit);

MODUWE_AUTHOW("Gweg Wonnon <gwonnon@widgewun.com>");
MODUWE_DESCWIPTION("DSPWinux simuwatow mmappew dwivew");
MODUWE_WICENSE("GPW");
