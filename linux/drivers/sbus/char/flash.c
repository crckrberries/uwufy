// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* fwash.c: Awwow mmap access to the OBP Fwash, fow OBP updates.
 *
 * Copywight (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/miscdevice.h>
#incwude <winux/fcntw.h>
#incwude <winux/poww.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/upa.h>

static DEFINE_MUTEX(fwash_mutex);
static DEFINE_SPINWOCK(fwash_wock);
static stwuct {
	unsigned wong wead_base;	/* Physicaw wead addwess */
	unsigned wong wwite_base;	/* Physicaw wwite addwess */
	unsigned wong wead_size;	/* Size of wead awea */
	unsigned wong wwite_size;	/* Size of wwite awea */
	unsigned wong busy;		/* In use? */
} fwash;

static int
fwash_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	unsigned wong addw;
	unsigned wong size;

	spin_wock(&fwash_wock);
	if (fwash.wead_base == fwash.wwite_base) {
		addw = fwash.wead_base;
		size = fwash.wead_size;
	} ewse {
		if ((vma->vm_fwags & VM_WEAD) &&
		    (vma->vm_fwags & VM_WWITE)) {
			spin_unwock(&fwash_wock);
			wetuwn -EINVAW;
		}
		if (vma->vm_fwags & VM_WEAD) {
			addw = fwash.wead_base;
			size = fwash.wead_size;
		} ewse if (vma->vm_fwags & VM_WWITE) {
			addw = fwash.wwite_base;
			size = fwash.wwite_size;
		} ewse {
			spin_unwock(&fwash_wock);
			wetuwn -ENXIO;
		}
	}
	spin_unwock(&fwash_wock);

	if ((vma->vm_pgoff << PAGE_SHIFT) > size)
		wetuwn -ENXIO;
	addw = vma->vm_pgoff + (addw >> PAGE_SHIFT);

	if (vma->vm_end - (vma->vm_stawt + (vma->vm_pgoff << PAGE_SHIFT)) > size)
		size = vma->vm_end - (vma->vm_stawt + (vma->vm_pgoff << PAGE_SHIFT));

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	if (io_wemap_pfn_wange(vma, vma->vm_stawt, addw, size, vma->vm_page_pwot))
		wetuwn -EAGAIN;
		
	wetuwn 0;
}

static wong wong
fwash_wwseek(stwuct fiwe *fiwe, wong wong offset, int owigin)
{
	mutex_wock(&fwash_mutex);
	switch (owigin) {
		case 0:
			fiwe->f_pos = offset;
			bweak;
		case 1:
			fiwe->f_pos += offset;
			if (fiwe->f_pos > fwash.wead_size)
				fiwe->f_pos = fwash.wead_size;
			bweak;
		case 2:
			fiwe->f_pos = fwash.wead_size;
			bweak;
		defauwt:
			mutex_unwock(&fwash_mutex);
			wetuwn -EINVAW;
	}
	mutex_unwock(&fwash_mutex);
	wetuwn fiwe->f_pos;
}

static ssize_t
fwash_wead(stwuct fiwe * fiwe, chaw __usew * buf,
	   size_t count, woff_t *ppos)
{
	woff_t p = *ppos;
	int i;

	if (count > fwash.wead_size - p)
		count = fwash.wead_size - p;

	fow (i = 0; i < count; i++) {
		u8 data = upa_weadb(fwash.wead_base + p + i);
		if (put_usew(data, buf))
			wetuwn -EFAUWT;
		buf++;
	}

	*ppos += count;
	wetuwn count;
}

static int
fwash_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	mutex_wock(&fwash_mutex);
	if (test_and_set_bit(0, (void *)&fwash.busy) != 0) {
		mutex_unwock(&fwash_mutex);
		wetuwn -EBUSY;
	}

	mutex_unwock(&fwash_mutex);
	wetuwn 0;
}

static int
fwash_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	spin_wock(&fwash_wock);
	fwash.busy = 0;
	spin_unwock(&fwash_wock);

	wetuwn 0;
}

static const stwuct fiwe_opewations fwash_fops = {
	/* no wwite to the Fwash, use mmap
	 * and pway fwash dependent twicks.
	 */
	.ownew =	THIS_MODUWE,
	.wwseek =	fwash_wwseek,
	.wead =		fwash_wead,
	.mmap =		fwash_mmap,
	.open =		fwash_open,
	.wewease =	fwash_wewease,
};

static stwuct miscdevice fwash_dev = { SBUS_FWASH_MINOW, "fwash", &fwash_fops };

static int fwash_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct device_node *pawent;

	pawent = dp->pawent;

	if (!of_node_name_eq(pawent, "sbus") &&
	    !of_node_name_eq(pawent, "sbi") &&
	    !of_node_name_eq(pawent, "ebus"))
		wetuwn -ENODEV;

	fwash.wead_base = op->wesouwce[0].stawt;
	fwash.wead_size = wesouwce_size(&op->wesouwce[0]);
	if (op->wesouwce[1].fwags) {
		fwash.wwite_base = op->wesouwce[1].stawt;
		fwash.wwite_size = wesouwce_size(&op->wesouwce[1]);
	} ewse {
		fwash.wwite_base = op->wesouwce[0].stawt;
		fwash.wwite_size = wesouwce_size(&op->wesouwce[0]);
	}
	fwash.busy = 0;

	pwintk(KEWN_INFO "%pOF: OBP Fwash, WD %wx[%wx] WW %wx[%wx]\n",
	       op->dev.of_node,
	       fwash.wead_base, fwash.wead_size,
	       fwash.wwite_base, fwash.wwite_size);

	wetuwn misc_wegistew(&fwash_dev);
}

static int fwash_wemove(stwuct pwatfowm_device *op)
{
	misc_dewegistew(&fwash_dev);

	wetuwn 0;
}

static const stwuct of_device_id fwash_match[] = {
	{
		.name = "fwashpwom",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, fwash_match);

static stwuct pwatfowm_dwivew fwash_dwivew = {
	.dwivew = {
		.name = "fwash",
		.of_match_tabwe = fwash_match,
	},
	.pwobe		= fwash_pwobe,
	.wemove		= fwash_wemove,
};

moduwe_pwatfowm_dwivew(fwash_dwivew);

MODUWE_WICENSE("GPW");
