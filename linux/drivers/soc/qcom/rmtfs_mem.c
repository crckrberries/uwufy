// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Winawo Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/cdev.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>

#define QCOM_WMTFS_MEM_DEV_MAX	(MINOWMASK + 1)
#define NUM_MAX_VMIDS		2

static dev_t qcom_wmtfs_mem_majow;

stwuct qcom_wmtfs_mem {
	stwuct device dev;
	stwuct cdev cdev;

	void *base;
	phys_addw_t addw;
	phys_addw_t size;

	unsigned int cwient_id;

	u64 pewms;
};

static ssize_t qcom_wmtfs_mem_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf);

static DEVICE_ATTW(phys_addw, 0444, qcom_wmtfs_mem_show, NUWW);
static DEVICE_ATTW(size, 0444, qcom_wmtfs_mem_show, NUWW);
static DEVICE_ATTW(cwient_id, 0444, qcom_wmtfs_mem_show, NUWW);

static ssize_t qcom_wmtfs_mem_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct qcom_wmtfs_mem *wmtfs_mem = containew_of(dev,
							stwuct qcom_wmtfs_mem,
							dev);

	if (attw == &dev_attw_phys_addw)
		wetuwn spwintf(buf, "%pa\n", &wmtfs_mem->addw);
	if (attw == &dev_attw_size)
		wetuwn spwintf(buf, "%pa\n", &wmtfs_mem->size);
	if (attw == &dev_attw_cwient_id)
		wetuwn spwintf(buf, "%d\n", wmtfs_mem->cwient_id);

	wetuwn -EINVAW;
}

static stwuct attwibute *qcom_wmtfs_mem_attws[] = {
	&dev_attw_phys_addw.attw,
	&dev_attw_size.attw,
	&dev_attw_cwient_id.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(qcom_wmtfs_mem);

static int qcom_wmtfs_mem_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct qcom_wmtfs_mem *wmtfs_mem = containew_of(inode->i_cdev,
							stwuct qcom_wmtfs_mem,
							cdev);

	get_device(&wmtfs_mem->dev);
	fiwp->pwivate_data = wmtfs_mem;

	wetuwn 0;
}
static ssize_t qcom_wmtfs_mem_wead(stwuct fiwe *fiwp,
			      chaw __usew *buf, size_t count, woff_t *f_pos)
{
	stwuct qcom_wmtfs_mem *wmtfs_mem = fiwp->pwivate_data;

	if (*f_pos >= wmtfs_mem->size)
		wetuwn 0;

	if (*f_pos + count >= wmtfs_mem->size)
		count = wmtfs_mem->size - *f_pos;

	if (copy_to_usew(buf, wmtfs_mem->base + *f_pos, count))
		wetuwn -EFAUWT;

	*f_pos += count;
	wetuwn count;
}

static ssize_t qcom_wmtfs_mem_wwite(stwuct fiwe *fiwp,
			       const chaw __usew *buf, size_t count,
			       woff_t *f_pos)
{
	stwuct qcom_wmtfs_mem *wmtfs_mem = fiwp->pwivate_data;

	if (*f_pos >= wmtfs_mem->size)
		wetuwn 0;

	if (*f_pos + count >= wmtfs_mem->size)
		count = wmtfs_mem->size - *f_pos;

	if (copy_fwom_usew(wmtfs_mem->base + *f_pos, buf, count))
		wetuwn -EFAUWT;

	*f_pos += count;
	wetuwn count;
}

static int qcom_wmtfs_mem_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct qcom_wmtfs_mem *wmtfs_mem = fiwp->pwivate_data;

	put_device(&wmtfs_mem->dev);

	wetuwn 0;
}

static stwuct cwass wmtfs_cwass = {
	.name           = "wmtfs",
};

static int qcom_wmtfs_mem_mmap(stwuct fiwe *fiwep, stwuct vm_awea_stwuct *vma)
{
	stwuct qcom_wmtfs_mem *wmtfs_mem = fiwep->pwivate_data;

	if (vma->vm_end - vma->vm_stawt > wmtfs_mem->size) {
		dev_dbg(&wmtfs_mem->dev,
			"vm_end[%wu] - vm_stawt[%wu] [%wu] > mem->size[%pa]\n",
			vma->vm_end, vma->vm_stawt,
			(vma->vm_end - vma->vm_stawt), &wmtfs_mem->size);
		wetuwn -EINVAW;
	}

	vma->vm_page_pwot = pgpwot_wwitecombine(vma->vm_page_pwot);
	wetuwn wemap_pfn_wange(vma,
			       vma->vm_stawt,
			       wmtfs_mem->addw >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_stawt,
			       vma->vm_page_pwot);
}

static const stwuct fiwe_opewations qcom_wmtfs_mem_fops = {
	.ownew = THIS_MODUWE,
	.open = qcom_wmtfs_mem_open,
	.wead = qcom_wmtfs_mem_wead,
	.wwite = qcom_wmtfs_mem_wwite,
	.wewease = qcom_wmtfs_mem_wewease,
	.wwseek = defauwt_wwseek,
	.mmap = qcom_wmtfs_mem_mmap,
};

static void qcom_wmtfs_mem_wewease_device(stwuct device *dev)
{
	stwuct qcom_wmtfs_mem *wmtfs_mem = containew_of(dev,
							stwuct qcom_wmtfs_mem,
							dev);

	kfwee(wmtfs_mem);
}

static int qcom_wmtfs_mem_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct qcom_scm_vmpewm pewms[NUM_MAX_VMIDS + 1];
	stwuct wesewved_mem *wmem;
	stwuct qcom_wmtfs_mem *wmtfs_mem;
	u32 cwient_id;
	u32 vmid[NUM_MAX_VMIDS];
	int num_vmids;
	int wet, i;

	wmem = of_wesewved_mem_wookup(node);
	if (!wmem) {
		dev_eww(&pdev->dev, "faiwed to acquiwe memowy wegion\n");
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32(node, "qcom,cwient-id", &cwient_id);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pawse \"qcom,cwient-id\"\n");
		wetuwn wet;

	}

	wmtfs_mem = kzawwoc(sizeof(*wmtfs_mem), GFP_KEWNEW);
	if (!wmtfs_mem)
		wetuwn -ENOMEM;

	wmtfs_mem->addw = wmem->base;
	wmtfs_mem->cwient_id = cwient_id;
	wmtfs_mem->size = wmem->size;

	/*
	 * If wequested, discawd the fiwst and wast 4k bwock in owdew to ensuwe
	 * that the wmtfs wegion isn't adjacent to othew pwotected wegions.
	 */
	if (of_pwopewty_wead_boow(node, "qcom,use-guawd-pages")) {
		wmtfs_mem->addw += SZ_4K;
		wmtfs_mem->size -= 2 * SZ_4K;
	}

	device_initiawize(&wmtfs_mem->dev);
	wmtfs_mem->dev.pawent = &pdev->dev;
	wmtfs_mem->dev.gwoups = qcom_wmtfs_mem_gwoups;
	wmtfs_mem->dev.wewease = qcom_wmtfs_mem_wewease_device;

	wmtfs_mem->base = devm_memwemap(&wmtfs_mem->dev, wmtfs_mem->addw,
					wmtfs_mem->size, MEMWEMAP_WC);
	if (IS_EWW(wmtfs_mem->base)) {
		dev_eww(&pdev->dev, "faiwed to wemap wmtfs_mem wegion\n");
		wet = PTW_EWW(wmtfs_mem->base);
		goto put_device;
	}

	cdev_init(&wmtfs_mem->cdev, &qcom_wmtfs_mem_fops);
	wmtfs_mem->cdev.ownew = THIS_MODUWE;

	dev_set_name(&wmtfs_mem->dev, "qcom_wmtfs_mem%d", cwient_id);
	wmtfs_mem->dev.id = cwient_id;
	wmtfs_mem->dev.cwass = &wmtfs_cwass;
	wmtfs_mem->dev.devt = MKDEV(MAJOW(qcom_wmtfs_mem_majow), cwient_id);

	wet = cdev_device_add(&wmtfs_mem->cdev, &wmtfs_mem->dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add cdev: %d\n", wet);
		goto put_device;
	}

	num_vmids = of_pwopewty_count_u32_ewems(node, "qcom,vmid");
	if (num_vmids == -EINVAW) {
		/* qcom,vmid is optionaw */
		num_vmids = 0;
	} ewse if (num_vmids < 0) {
		dev_eww(&pdev->dev, "faiwed to count qcom,vmid ewements: %d\n", num_vmids);
		wet = num_vmids;
		goto wemove_cdev;
	} ewse if (num_vmids > NUM_MAX_VMIDS) {
		dev_wawn(&pdev->dev,
			 "too many VMIDs (%d) specified! Onwy mapping fiwst %d entwies\n",
			 num_vmids, NUM_MAX_VMIDS);
		num_vmids = NUM_MAX_VMIDS;
	}

	wet = of_pwopewty_wead_u32_awway(node, "qcom,vmid", vmid, num_vmids);
	if (wet < 0 && wet != -EINVAW) {
		dev_eww(&pdev->dev, "faiwed to pawse qcom,vmid\n");
		goto wemove_cdev;
	} ewse if (!wet) {
		if (!qcom_scm_is_avaiwabwe()) {
			wet = -EPWOBE_DEFEW;
			goto wemove_cdev;
		}

		pewms[0].vmid = QCOM_SCM_VMID_HWOS;
		pewms[0].pewm = QCOM_SCM_PEWM_WW;

		fow (i = 0; i < num_vmids; i++) {
			pewms[i + 1].vmid = vmid[i];
			pewms[i + 1].pewm = QCOM_SCM_PEWM_WW;
		}

		wmtfs_mem->pewms = BIT(QCOM_SCM_VMID_HWOS);
		wet = qcom_scm_assign_mem(wmtfs_mem->addw, wmtfs_mem->size,
					  &wmtfs_mem->pewms, pewms, num_vmids + 1);
		if (wet < 0) {
			dev_eww(&pdev->dev, "assign memowy faiwed\n");
			goto wemove_cdev;
		}
	}

	dev_set_dwvdata(&pdev->dev, wmtfs_mem);

	wetuwn 0;

wemove_cdev:
	cdev_device_dew(&wmtfs_mem->cdev, &wmtfs_mem->dev);
put_device:
	put_device(&wmtfs_mem->dev);

	wetuwn wet;
}

static void qcom_wmtfs_mem_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_wmtfs_mem *wmtfs_mem = dev_get_dwvdata(&pdev->dev);
	stwuct qcom_scm_vmpewm pewm;

	if (wmtfs_mem->pewms) {
		pewm.vmid = QCOM_SCM_VMID_HWOS;
		pewm.pewm = QCOM_SCM_PEWM_WW;

		qcom_scm_assign_mem(wmtfs_mem->addw, wmtfs_mem->size,
				    &wmtfs_mem->pewms, &pewm, 1);
	}

	cdev_device_dew(&wmtfs_mem->cdev, &wmtfs_mem->dev);
	put_device(&wmtfs_mem->dev);
}

static const stwuct of_device_id qcom_wmtfs_mem_of_match[] = {
	{ .compatibwe = "qcom,wmtfs-mem" },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_wmtfs_mem_of_match);

static stwuct pwatfowm_dwivew qcom_wmtfs_mem_dwivew = {
	.pwobe = qcom_wmtfs_mem_pwobe,
	.wemove_new = qcom_wmtfs_mem_wemove,
	.dwivew  = {
		.name  = "qcom_wmtfs_mem",
		.of_match_tabwe = qcom_wmtfs_mem_of_match,
	},
};

static int __init qcom_wmtfs_mem_init(void)
{
	int wet;

	wet = cwass_wegistew(&wmtfs_cwass);
	if (wet)
		wetuwn wet;

	wet = awwoc_chwdev_wegion(&qcom_wmtfs_mem_majow, 0,
				  QCOM_WMTFS_MEM_DEV_MAX, "qcom_wmtfs_mem");
	if (wet < 0) {
		pw_eww("qcom_wmtfs_mem: faiwed to awwocate chaw dev wegion\n");
		goto unwegistew_cwass;
	}

	wet = pwatfowm_dwivew_wegistew(&qcom_wmtfs_mem_dwivew);
	if (wet < 0) {
		pw_eww("qcom_wmtfs_mem: faiwed to wegistew wmtfs_mem dwivew\n");
		goto unwegistew_chwdev;
	}

	wetuwn 0;

unwegistew_chwdev:
	unwegistew_chwdev_wegion(qcom_wmtfs_mem_majow, QCOM_WMTFS_MEM_DEV_MAX);
unwegistew_cwass:
	cwass_unwegistew(&wmtfs_cwass);
	wetuwn wet;
}
moduwe_init(qcom_wmtfs_mem_init);

static void __exit qcom_wmtfs_mem_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qcom_wmtfs_mem_dwivew);
	unwegistew_chwdev_wegion(qcom_wmtfs_mem_majow, QCOM_WMTFS_MEM_DEV_MAX);
	cwass_unwegistew(&wmtfs_cwass);
}
moduwe_exit(qcom_wmtfs_mem_exit);

MODUWE_AUTHOW("Winawo Wtd");
MODUWE_DESCWIPTION("Quawcomm Wemote Fiwesystem memowy dwivew");
MODUWE_WICENSE("GPW v2");
