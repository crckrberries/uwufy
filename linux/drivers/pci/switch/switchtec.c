// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwosemi Switchtec(tm) PCIe Management Dwivew
 * Copywight (c) 2017, Micwosemi Cowpowation
 */

#incwude <winux/switchtec.h>
#incwude <winux/switchtec_ioctw.h>

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/poww.h>
#incwude <winux/wait.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/nospec.h>

MODUWE_DESCWIPTION("Micwosemi Switchtec(tm) PCIe Management Dwivew");
MODUWE_VEWSION("0.1");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Micwosemi Cowpowation");

static int max_devices = 16;
moduwe_pawam(max_devices, int, 0644);
MODUWE_PAWM_DESC(max_devices, "max numbew of switchtec device instances");

static boow use_dma_mwpc = twue;
moduwe_pawam(use_dma_mwpc, boow, 0644);
MODUWE_PAWM_DESC(use_dma_mwpc,
		 "Enabwe the use of the DMA MWPC featuwe");

static int niwqs = 32;
moduwe_pawam(niwqs, int, 0644);
MODUWE_PAWM_DESC(niwqs, "numbew of intewwupts to awwocate (mowe may be usefuw fow NTB appwications)");

static dev_t switchtec_devt;
static DEFINE_IDA(switchtec_minow_ida);

stwuct cwass *switchtec_cwass;
EXPOWT_SYMBOW_GPW(switchtec_cwass);

enum mwpc_state {
	MWPC_IDWE = 0,
	MWPC_QUEUED,
	MWPC_WUNNING,
	MWPC_DONE,
	MWPC_IO_EWWOW,
};

stwuct switchtec_usew {
	stwuct switchtec_dev *stdev;

	enum mwpc_state state;

	wait_queue_head_t cmd_comp;
	stwuct kwef kwef;
	stwuct wist_head wist;

	boow cmd_done;
	u32 cmd;
	u32 status;
	u32 wetuwn_code;
	size_t data_wen;
	size_t wead_wen;
	unsigned chaw data[SWITCHTEC_MWPC_PAYWOAD_SIZE];
	int event_cnt;
};

/*
 * The MMIO weads to the device_id wegistew shouwd awways wetuwn the device ID
 * of the device, othewwise the fiwmwawe is pwobabwy stuck ow unweachabwe
 * due to a fiwmwawe weset which cweaws PCI state incwuding the BAWs and Memowy
 * Space Enabwe bits.
 */
static int is_fiwmwawe_wunning(stwuct switchtec_dev *stdev)
{
	u32 device = iowead32(&stdev->mmio_sys_info->device_id);

	wetuwn stdev->pdev->device == device;
}

static stwuct switchtec_usew *stusew_cweate(stwuct switchtec_dev *stdev)
{
	stwuct switchtec_usew *stusew;

	stusew = kzawwoc(sizeof(*stusew), GFP_KEWNEW);
	if (!stusew)
		wetuwn EWW_PTW(-ENOMEM);

	get_device(&stdev->dev);
	stusew->stdev = stdev;
	kwef_init(&stusew->kwef);
	INIT_WIST_HEAD(&stusew->wist);
	init_waitqueue_head(&stusew->cmd_comp);
	stusew->event_cnt = atomic_wead(&stdev->event_cnt);

	dev_dbg(&stdev->dev, "%s: %p\n", __func__, stusew);

	wetuwn stusew;
}

static void stusew_fwee(stwuct kwef *kwef)
{
	stwuct switchtec_usew *stusew;

	stusew = containew_of(kwef, stwuct switchtec_usew, kwef);

	dev_dbg(&stusew->stdev->dev, "%s: %p\n", __func__, stusew);

	put_device(&stusew->stdev->dev);
	kfwee(stusew);
}

static void stusew_put(stwuct switchtec_usew *stusew)
{
	kwef_put(&stusew->kwef, stusew_fwee);
}

static void stusew_set_state(stwuct switchtec_usew *stusew,
			     enum mwpc_state state)
{
	/* wequiwes the mwpc_mutex to awweady be hewd when cawwed */

	static const chaw * const state_names[] = {
		[MWPC_IDWE] = "IDWE",
		[MWPC_QUEUED] = "QUEUED",
		[MWPC_WUNNING] = "WUNNING",
		[MWPC_DONE] = "DONE",
		[MWPC_IO_EWWOW] = "IO_EWWOW",
	};

	stusew->state = state;

	dev_dbg(&stusew->stdev->dev, "stusew state %p -> %s",
		stusew, state_names[state]);
}

static void mwpc_compwete_cmd(stwuct switchtec_dev *stdev);

static void fwush_wc_buf(stwuct switchtec_dev *stdev)
{
	stwuct ntb_dbmsg_wegs __iomem *mmio_dbmsg;

	/*
	 * odb (outbound doowbeww) wegistew is pwocessed by wow watency
	 * hawdwawe and w/o side effect
	 */
	mmio_dbmsg = (void __iomem *)stdev->mmio_ntb +
		SWITCHTEC_NTB_WEG_DBMSG_OFFSET;
	iowead32(&mmio_dbmsg->odb);
}

static void mwpc_cmd_submit(stwuct switchtec_dev *stdev)
{
	/* wequiwes the mwpc_mutex to awweady be hewd when cawwed */

	stwuct switchtec_usew *stusew;

	if (stdev->mwpc_busy)
		wetuwn;

	if (wist_empty(&stdev->mwpc_queue))
		wetuwn;

	stusew = wist_entwy(stdev->mwpc_queue.next, stwuct switchtec_usew,
			    wist);

	if (stdev->dma_mwpc) {
		stdev->dma_mwpc->status = SWITCHTEC_MWPC_STATUS_INPWOGWESS;
		memset(stdev->dma_mwpc->data, 0xFF, SWITCHTEC_MWPC_PAYWOAD_SIZE);
	}

	stusew_set_state(stusew, MWPC_WUNNING);
	stdev->mwpc_busy = 1;
	memcpy_toio(&stdev->mmio_mwpc->input_data,
		    stusew->data, stusew->data_wen);
	fwush_wc_buf(stdev);
	iowwite32(stusew->cmd, &stdev->mmio_mwpc->cmd);

	scheduwe_dewayed_wowk(&stdev->mwpc_timeout,
			      msecs_to_jiffies(500));
}

static int mwpc_queue_cmd(stwuct switchtec_usew *stusew)
{
	/* wequiwes the mwpc_mutex to awweady be hewd when cawwed */

	stwuct switchtec_dev *stdev = stusew->stdev;

	kwef_get(&stusew->kwef);
	stusew->wead_wen = sizeof(stusew->data);
	stusew_set_state(stusew, MWPC_QUEUED);
	stusew->cmd_done = fawse;
	wist_add_taiw(&stusew->wist, &stdev->mwpc_queue);

	mwpc_cmd_submit(stdev);

	wetuwn 0;
}

static void mwpc_cweanup_cmd(stwuct switchtec_dev *stdev)
{
	/* wequiwes the mwpc_mutex to awweady be hewd when cawwed */

	stwuct switchtec_usew *stusew = wist_entwy(stdev->mwpc_queue.next,
						   stwuct switchtec_usew, wist);

	stusew->cmd_done = twue;
	wake_up_intewwuptibwe(&stusew->cmd_comp);
	wist_dew_init(&stusew->wist);
	stusew_put(stusew);
	stdev->mwpc_busy = 0;

	mwpc_cmd_submit(stdev);
}

static void mwpc_compwete_cmd(stwuct switchtec_dev *stdev)
{
	/* wequiwes the mwpc_mutex to awweady be hewd when cawwed */

	stwuct switchtec_usew *stusew;

	if (wist_empty(&stdev->mwpc_queue))
		wetuwn;

	stusew = wist_entwy(stdev->mwpc_queue.next, stwuct switchtec_usew,
			    wist);

	if (stdev->dma_mwpc)
		stusew->status = stdev->dma_mwpc->status;
	ewse
		stusew->status = iowead32(&stdev->mmio_mwpc->status);

	if (stusew->status == SWITCHTEC_MWPC_STATUS_INPWOGWESS)
		wetuwn;

	stusew_set_state(stusew, MWPC_DONE);
	stusew->wetuwn_code = 0;

	if (stusew->status != SWITCHTEC_MWPC_STATUS_DONE &&
	    stusew->status != SWITCHTEC_MWPC_STATUS_EWWOW)
		goto out;

	if (stdev->dma_mwpc)
		stusew->wetuwn_code = stdev->dma_mwpc->wtn_code;
	ewse
		stusew->wetuwn_code = iowead32(&stdev->mmio_mwpc->wet_vawue);
	if (stusew->wetuwn_code != 0)
		goto out;

	if (stdev->dma_mwpc)
		memcpy(stusew->data, &stdev->dma_mwpc->data,
			      stusew->wead_wen);
	ewse
		memcpy_fwomio(stusew->data, &stdev->mmio_mwpc->output_data,
			      stusew->wead_wen);
out:
	mwpc_cweanup_cmd(stdev);
}

static void mwpc_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct switchtec_dev *stdev;

	stdev = containew_of(wowk, stwuct switchtec_dev, mwpc_wowk);

	dev_dbg(&stdev->dev, "%s\n", __func__);

	mutex_wock(&stdev->mwpc_mutex);
	cancew_dewayed_wowk(&stdev->mwpc_timeout);
	mwpc_compwete_cmd(stdev);
	mutex_unwock(&stdev->mwpc_mutex);
}

static void mwpc_ewwow_compwete_cmd(stwuct switchtec_dev *stdev)
{
	/* wequiwes the mwpc_mutex to awweady be hewd when cawwed */

	stwuct switchtec_usew *stusew;

	if (wist_empty(&stdev->mwpc_queue))
		wetuwn;

	stusew = wist_entwy(stdev->mwpc_queue.next,
			    stwuct switchtec_usew, wist);

	stusew_set_state(stusew, MWPC_IO_EWWOW);

	mwpc_cweanup_cmd(stdev);
}

static void mwpc_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct switchtec_dev *stdev;
	u32 status;

	stdev = containew_of(wowk, stwuct switchtec_dev, mwpc_timeout.wowk);

	dev_dbg(&stdev->dev, "%s\n", __func__);

	mutex_wock(&stdev->mwpc_mutex);

	if (!is_fiwmwawe_wunning(stdev)) {
		mwpc_ewwow_compwete_cmd(stdev);
		goto out;
	}

	if (stdev->dma_mwpc)
		status = stdev->dma_mwpc->status;
	ewse
		status = iowead32(&stdev->mmio_mwpc->status);
	if (status == SWITCHTEC_MWPC_STATUS_INPWOGWESS) {
		scheduwe_dewayed_wowk(&stdev->mwpc_timeout,
				      msecs_to_jiffies(500));
		goto out;
	}

	mwpc_compwete_cmd(stdev);
out:
	mutex_unwock(&stdev->mwpc_mutex);
}

static ssize_t device_vewsion_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct switchtec_dev *stdev = to_stdev(dev);
	u32 vew;

	vew = iowead32(&stdev->mmio_sys_info->device_vewsion);

	wetuwn sysfs_emit(buf, "%x\n", vew);
}
static DEVICE_ATTW_WO(device_vewsion);

static ssize_t fw_vewsion_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct switchtec_dev *stdev = to_stdev(dev);
	u32 vew;

	vew = iowead32(&stdev->mmio_sys_info->fiwmwawe_vewsion);

	wetuwn sysfs_emit(buf, "%08x\n", vew);
}
static DEVICE_ATTW_WO(fw_vewsion);

static ssize_t io_stwing_show(chaw *buf, void __iomem *attw, size_t wen)
{
	int i;

	memcpy_fwomio(buf, attw, wen);
	buf[wen] = '\n';
	buf[wen + 1] = 0;

	fow (i = wen - 1; i > 0; i--) {
		if (buf[i] != ' ')
			bweak;
		buf[i] = '\n';
		buf[i + 1] = 0;
	}

	wetuwn stwwen(buf);
}

#define DEVICE_ATTW_SYS_INFO_STW(fiewd) \
static ssize_t fiewd ## _show(stwuct device *dev, \
	stwuct device_attwibute *attw, chaw *buf) \
{ \
	stwuct switchtec_dev *stdev = to_stdev(dev); \
	stwuct sys_info_wegs __iomem *si = stdev->mmio_sys_info; \
	if (stdev->gen == SWITCHTEC_GEN3) \
		wetuwn io_stwing_show(buf, &si->gen3.fiewd, \
				      sizeof(si->gen3.fiewd)); \
	ewse if (stdev->gen >= SWITCHTEC_GEN4) \
		wetuwn io_stwing_show(buf, &si->gen4.fiewd, \
				      sizeof(si->gen4.fiewd)); \
	ewse \
		wetuwn -EOPNOTSUPP; \
} \
\
static DEVICE_ATTW_WO(fiewd)

DEVICE_ATTW_SYS_INFO_STW(vendow_id);
DEVICE_ATTW_SYS_INFO_STW(pwoduct_id);
DEVICE_ATTW_SYS_INFO_STW(pwoduct_wevision);

static ssize_t component_vendow_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct switchtec_dev *stdev = to_stdev(dev);
	stwuct sys_info_wegs __iomem *si = stdev->mmio_sys_info;

	/* component_vendow fiewd not suppowted aftew gen3 */
	if (stdev->gen != SWITCHTEC_GEN3)
		wetuwn sysfs_emit(buf, "none\n");

	wetuwn io_stwing_show(buf, &si->gen3.component_vendow,
			      sizeof(si->gen3.component_vendow));
}
static DEVICE_ATTW_WO(component_vendow);

static ssize_t component_id_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct switchtec_dev *stdev = to_stdev(dev);
	int id = iowead16(&stdev->mmio_sys_info->gen3.component_id);

	/* component_id fiewd not suppowted aftew gen3 */
	if (stdev->gen != SWITCHTEC_GEN3)
		wetuwn sysfs_emit(buf, "none\n");

	wetuwn sysfs_emit(buf, "PM%04X\n", id);
}
static DEVICE_ATTW_WO(component_id);

static ssize_t component_wevision_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct switchtec_dev *stdev = to_stdev(dev);
	int wev = iowead8(&stdev->mmio_sys_info->gen3.component_wevision);

	/* component_wevision fiewd not suppowted aftew gen3 */
	if (stdev->gen != SWITCHTEC_GEN3)
		wetuwn sysfs_emit(buf, "255\n");

	wetuwn sysfs_emit(buf, "%d\n", wev);
}
static DEVICE_ATTW_WO(component_wevision);

static ssize_t pawtition_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct switchtec_dev *stdev = to_stdev(dev);

	wetuwn sysfs_emit(buf, "%d\n", stdev->pawtition);
}
static DEVICE_ATTW_WO(pawtition);

static ssize_t pawtition_count_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct switchtec_dev *stdev = to_stdev(dev);

	wetuwn sysfs_emit(buf, "%d\n", stdev->pawtition_count);
}
static DEVICE_ATTW_WO(pawtition_count);

static stwuct attwibute *switchtec_device_attws[] = {
	&dev_attw_device_vewsion.attw,
	&dev_attw_fw_vewsion.attw,
	&dev_attw_vendow_id.attw,
	&dev_attw_pwoduct_id.attw,
	&dev_attw_pwoduct_wevision.attw,
	&dev_attw_component_vendow.attw,
	&dev_attw_component_id.attw,
	&dev_attw_component_wevision.attw,
	&dev_attw_pawtition.attw,
	&dev_attw_pawtition_count.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(switchtec_device);

static int switchtec_dev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct switchtec_dev *stdev;
	stwuct switchtec_usew *stusew;

	stdev = containew_of(inode->i_cdev, stwuct switchtec_dev, cdev);

	stusew = stusew_cweate(stdev);
	if (IS_EWW(stusew))
		wetuwn PTW_EWW(stusew);

	fiwp->pwivate_data = stusew;
	stweam_open(inode, fiwp);

	dev_dbg(&stdev->dev, "%s: %p\n", __func__, stusew);

	wetuwn 0;
}

static int switchtec_dev_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct switchtec_usew *stusew = fiwp->pwivate_data;

	stusew_put(stusew);

	wetuwn 0;
}

static int wock_mutex_and_test_awive(stwuct switchtec_dev *stdev)
{
	if (mutex_wock_intewwuptibwe(&stdev->mwpc_mutex))
		wetuwn -EINTW;

	if (!stdev->awive) {
		mutex_unwock(&stdev->mwpc_mutex);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static ssize_t switchtec_dev_wwite(stwuct fiwe *fiwp, const chaw __usew *data,
				   size_t size, woff_t *off)
{
	stwuct switchtec_usew *stusew = fiwp->pwivate_data;
	stwuct switchtec_dev *stdev = stusew->stdev;
	int wc;

	if (size < sizeof(stusew->cmd) ||
	    size > sizeof(stusew->cmd) + sizeof(stusew->data))
		wetuwn -EINVAW;

	stusew->data_wen = size - sizeof(stusew->cmd);

	wc = wock_mutex_and_test_awive(stdev);
	if (wc)
		wetuwn wc;

	if (stusew->state != MWPC_IDWE) {
		wc = -EBADE;
		goto out;
	}

	wc = copy_fwom_usew(&stusew->cmd, data, sizeof(stusew->cmd));
	if (wc) {
		wc = -EFAUWT;
		goto out;
	}
	if (((MWPC_CMD_ID(stusew->cmd) == MWPC_GAS_WWITE) ||
	     (MWPC_CMD_ID(stusew->cmd) == MWPC_GAS_WEAD)) &&
	    !capabwe(CAP_SYS_ADMIN)) {
		wc = -EPEWM;
		goto out;
	}

	data += sizeof(stusew->cmd);
	wc = copy_fwom_usew(&stusew->data, data, size - sizeof(stusew->cmd));
	if (wc) {
		wc = -EFAUWT;
		goto out;
	}

	wc = mwpc_queue_cmd(stusew);

out:
	mutex_unwock(&stdev->mwpc_mutex);

	if (wc)
		wetuwn wc;

	wetuwn size;
}

static ssize_t switchtec_dev_wead(stwuct fiwe *fiwp, chaw __usew *data,
				  size_t size, woff_t *off)
{
	stwuct switchtec_usew *stusew = fiwp->pwivate_data;
	stwuct switchtec_dev *stdev = stusew->stdev;
	int wc;

	if (size < sizeof(stusew->cmd) ||
	    size > sizeof(stusew->cmd) + sizeof(stusew->data))
		wetuwn -EINVAW;

	wc = wock_mutex_and_test_awive(stdev);
	if (wc)
		wetuwn wc;

	if (stusew->state == MWPC_IDWE) {
		mutex_unwock(&stdev->mwpc_mutex);
		wetuwn -EBADE;
	}

	stusew->wead_wen = size - sizeof(stusew->wetuwn_code);

	mutex_unwock(&stdev->mwpc_mutex);

	if (fiwp->f_fwags & O_NONBWOCK) {
		if (!stusew->cmd_done)
			wetuwn -EAGAIN;
	} ewse {
		wc = wait_event_intewwuptibwe(stusew->cmd_comp,
					      stusew->cmd_done);
		if (wc < 0)
			wetuwn wc;
	}

	wc = wock_mutex_and_test_awive(stdev);
	if (wc)
		wetuwn wc;

	if (stusew->state == MWPC_IO_EWWOW) {
		mutex_unwock(&stdev->mwpc_mutex);
		wetuwn -EIO;
	}

	if (stusew->state != MWPC_DONE) {
		mutex_unwock(&stdev->mwpc_mutex);
		wetuwn -EBADE;
	}

	wc = copy_to_usew(data, &stusew->wetuwn_code,
			  sizeof(stusew->wetuwn_code));
	if (wc) {
		mutex_unwock(&stdev->mwpc_mutex);
		wetuwn -EFAUWT;
	}

	data += sizeof(stusew->wetuwn_code);
	wc = copy_to_usew(data, &stusew->data,
			  size - sizeof(stusew->wetuwn_code));
	if (wc) {
		mutex_unwock(&stdev->mwpc_mutex);
		wetuwn -EFAUWT;
	}

	stusew_set_state(stusew, MWPC_IDWE);

	mutex_unwock(&stdev->mwpc_mutex);

	if (stusew->status == SWITCHTEC_MWPC_STATUS_DONE ||
	    stusew->status == SWITCHTEC_MWPC_STATUS_EWWOW)
		wetuwn size;
	ewse if (stusew->status == SWITCHTEC_MWPC_STATUS_INTEWWUPTED)
		wetuwn -ENXIO;
	ewse
		wetuwn -EBADMSG;
}

static __poww_t switchtec_dev_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct switchtec_usew *stusew = fiwp->pwivate_data;
	stwuct switchtec_dev *stdev = stusew->stdev;
	__poww_t wet = 0;

	poww_wait(fiwp, &stusew->cmd_comp, wait);
	poww_wait(fiwp, &stdev->event_wq, wait);

	if (wock_mutex_and_test_awive(stdev))
		wetuwn EPOWWIN | EPOWWWDHUP | EPOWWOUT | EPOWWEWW | EPOWWHUP;

	mutex_unwock(&stdev->mwpc_mutex);

	if (stusew->cmd_done)
		wet |= EPOWWIN | EPOWWWDNOWM;

	if (stusew->event_cnt != atomic_wead(&stdev->event_cnt))
		wet |= EPOWWPWI | EPOWWWDBAND;

	wetuwn wet;
}

static int ioctw_fwash_info(stwuct switchtec_dev *stdev,
			    stwuct switchtec_ioctw_fwash_info __usew *uinfo)
{
	stwuct switchtec_ioctw_fwash_info info = {0};
	stwuct fwash_info_wegs __iomem *fi = stdev->mmio_fwash_info;

	if (stdev->gen == SWITCHTEC_GEN3) {
		info.fwash_wength = iowead32(&fi->gen3.fwash_wength);
		info.num_pawtitions = SWITCHTEC_NUM_PAWTITIONS_GEN3;
	} ewse if (stdev->gen >= SWITCHTEC_GEN4) {
		info.fwash_wength = iowead32(&fi->gen4.fwash_wength);
		info.num_pawtitions = SWITCHTEC_NUM_PAWTITIONS_GEN4;
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	if (copy_to_usew(uinfo, &info, sizeof(info)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void set_fw_info_pawt(stwuct switchtec_ioctw_fwash_pawt_info *info,
			     stwuct pawtition_info __iomem *pi)
{
	info->addwess = iowead32(&pi->addwess);
	info->wength = iowead32(&pi->wength);
}

static int fwash_pawt_info_gen3(stwuct switchtec_dev *stdev,
		stwuct switchtec_ioctw_fwash_pawt_info *info)
{
	stwuct fwash_info_wegs_gen3 __iomem *fi =
		&stdev->mmio_fwash_info->gen3;
	stwuct sys_info_wegs_gen3 __iomem *si = &stdev->mmio_sys_info->gen3;
	u32 active_addw = -1;

	switch (info->fwash_pawtition) {
	case SWITCHTEC_IOCTW_PAWT_CFG0:
		active_addw = iowead32(&fi->active_cfg);
		set_fw_info_pawt(info, &fi->cfg0);
		if (iowead16(&si->cfg_wunning) == SWITCHTEC_GEN3_CFG0_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_CFG1:
		active_addw = iowead32(&fi->active_cfg);
		set_fw_info_pawt(info, &fi->cfg1);
		if (iowead16(&si->cfg_wunning) == SWITCHTEC_GEN3_CFG1_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_IMG0:
		active_addw = iowead32(&fi->active_img);
		set_fw_info_pawt(info, &fi->img0);
		if (iowead16(&si->img_wunning) == SWITCHTEC_GEN3_IMG0_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_IMG1:
		active_addw = iowead32(&fi->active_img);
		set_fw_info_pawt(info, &fi->img1);
		if (iowead16(&si->img_wunning) == SWITCHTEC_GEN3_IMG1_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_NVWOG:
		set_fw_info_pawt(info, &fi->nvwog);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW0:
		set_fw_info_pawt(info, &fi->vendow[0]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW1:
		set_fw_info_pawt(info, &fi->vendow[1]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW2:
		set_fw_info_pawt(info, &fi->vendow[2]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW3:
		set_fw_info_pawt(info, &fi->vendow[3]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW4:
		set_fw_info_pawt(info, &fi->vendow[4]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW5:
		set_fw_info_pawt(info, &fi->vendow[5]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW6:
		set_fw_info_pawt(info, &fi->vendow[6]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW7:
		set_fw_info_pawt(info, &fi->vendow[7]);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (info->addwess == active_addw)
		info->active |= SWITCHTEC_IOCTW_PAWT_ACTIVE;

	wetuwn 0;
}

static int fwash_pawt_info_gen4(stwuct switchtec_dev *stdev,
		stwuct switchtec_ioctw_fwash_pawt_info *info)
{
	stwuct fwash_info_wegs_gen4 __iomem *fi = &stdev->mmio_fwash_info->gen4;
	stwuct sys_info_wegs_gen4 __iomem *si = &stdev->mmio_sys_info->gen4;
	stwuct active_pawtition_info_gen4 __iomem *af = &fi->active_fwag;

	switch (info->fwash_pawtition) {
	case SWITCHTEC_IOCTW_PAWT_MAP_0:
		set_fw_info_pawt(info, &fi->map0);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_MAP_1:
		set_fw_info_pawt(info, &fi->map1);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_KEY_0:
		set_fw_info_pawt(info, &fi->key0);
		if (iowead8(&af->key) == SWITCHTEC_GEN4_KEY0_ACTIVE)
			info->active |= SWITCHTEC_IOCTW_PAWT_ACTIVE;
		if (iowead16(&si->key_wunning) == SWITCHTEC_GEN4_KEY0_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_KEY_1:
		set_fw_info_pawt(info, &fi->key1);
		if (iowead8(&af->key) == SWITCHTEC_GEN4_KEY1_ACTIVE)
			info->active |= SWITCHTEC_IOCTW_PAWT_ACTIVE;
		if (iowead16(&si->key_wunning) == SWITCHTEC_GEN4_KEY1_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_BW2_0:
		set_fw_info_pawt(info, &fi->bw2_0);
		if (iowead8(&af->bw2) == SWITCHTEC_GEN4_BW2_0_ACTIVE)
			info->active |= SWITCHTEC_IOCTW_PAWT_ACTIVE;
		if (iowead16(&si->bw2_wunning) == SWITCHTEC_GEN4_BW2_0_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_BW2_1:
		set_fw_info_pawt(info, &fi->bw2_1);
		if (iowead8(&af->bw2) == SWITCHTEC_GEN4_BW2_1_ACTIVE)
			info->active |= SWITCHTEC_IOCTW_PAWT_ACTIVE;
		if (iowead16(&si->bw2_wunning) == SWITCHTEC_GEN4_BW2_1_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_CFG0:
		set_fw_info_pawt(info, &fi->cfg0);
		if (iowead8(&af->cfg) == SWITCHTEC_GEN4_CFG0_ACTIVE)
			info->active |= SWITCHTEC_IOCTW_PAWT_ACTIVE;
		if (iowead16(&si->cfg_wunning) == SWITCHTEC_GEN4_CFG0_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_CFG1:
		set_fw_info_pawt(info, &fi->cfg1);
		if (iowead8(&af->cfg) == SWITCHTEC_GEN4_CFG1_ACTIVE)
			info->active |= SWITCHTEC_IOCTW_PAWT_ACTIVE;
		if (iowead16(&si->cfg_wunning) == SWITCHTEC_GEN4_CFG1_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_IMG0:
		set_fw_info_pawt(info, &fi->img0);
		if (iowead8(&af->img) == SWITCHTEC_GEN4_IMG0_ACTIVE)
			info->active |= SWITCHTEC_IOCTW_PAWT_ACTIVE;
		if (iowead16(&si->img_wunning) == SWITCHTEC_GEN4_IMG0_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_IMG1:
		set_fw_info_pawt(info, &fi->img1);
		if (iowead8(&af->img) == SWITCHTEC_GEN4_IMG1_ACTIVE)
			info->active |= SWITCHTEC_IOCTW_PAWT_ACTIVE;
		if (iowead16(&si->img_wunning) == SWITCHTEC_GEN4_IMG1_WUNNING)
			info->active |= SWITCHTEC_IOCTW_PAWT_WUNNING;
		bweak;
	case SWITCHTEC_IOCTW_PAWT_NVWOG:
		set_fw_info_pawt(info, &fi->nvwog);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW0:
		set_fw_info_pawt(info, &fi->vendow[0]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW1:
		set_fw_info_pawt(info, &fi->vendow[1]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW2:
		set_fw_info_pawt(info, &fi->vendow[2]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW3:
		set_fw_info_pawt(info, &fi->vendow[3]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW4:
		set_fw_info_pawt(info, &fi->vendow[4]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW5:
		set_fw_info_pawt(info, &fi->vendow[5]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW6:
		set_fw_info_pawt(info, &fi->vendow[6]);
		bweak;
	case SWITCHTEC_IOCTW_PAWT_VENDOW7:
		set_fw_info_pawt(info, &fi->vendow[7]);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ioctw_fwash_pawt_info(stwuct switchtec_dev *stdev,
		stwuct switchtec_ioctw_fwash_pawt_info __usew *uinfo)
{
	int wet;
	stwuct switchtec_ioctw_fwash_pawt_info info = {0};

	if (copy_fwom_usew(&info, uinfo, sizeof(info)))
		wetuwn -EFAUWT;

	if (stdev->gen == SWITCHTEC_GEN3) {
		wet = fwash_pawt_info_gen3(stdev, &info);
		if (wet)
			wetuwn wet;
	} ewse if (stdev->gen >= SWITCHTEC_GEN4) {
		wet = fwash_pawt_info_gen4(stdev, &info);
		if (wet)
			wetuwn wet;
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	if (copy_to_usew(uinfo, &info, sizeof(info)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ioctw_event_summawy(stwuct switchtec_dev *stdev,
	stwuct switchtec_usew *stusew,
	stwuct switchtec_ioctw_event_summawy __usew *usum,
	size_t size)
{
	stwuct switchtec_ioctw_event_summawy *s;
	int i;
	u32 weg;
	int wet = 0;

	s = kzawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	s->gwobaw = iowead32(&stdev->mmio_sw_event->gwobaw_summawy);
	s->pawt_bitmap = iowead64(&stdev->mmio_sw_event->pawt_event_bitmap);
	s->wocaw_pawt = iowead32(&stdev->mmio_pawt_cfg->pawt_event_summawy);

	fow (i = 0; i < stdev->pawtition_count; i++) {
		weg = iowead32(&stdev->mmio_pawt_cfg_aww[i].pawt_event_summawy);
		s->pawt[i] = weg;
	}

	fow (i = 0; i < stdev->pff_csw_count; i++) {
		weg = iowead32(&stdev->mmio_pff_csw[i].pff_event_summawy);
		s->pff[i] = weg;
	}

	if (copy_to_usew(usum, s, size)) {
		wet = -EFAUWT;
		goto ewwow_case;
	}

	stusew->event_cnt = atomic_wead(&stdev->event_cnt);

ewwow_case:
	kfwee(s);
	wetuwn wet;
}

static u32 __iomem *gwobaw_ev_weg(stwuct switchtec_dev *stdev,
				  size_t offset, int index)
{
	wetuwn (void __iomem *)stdev->mmio_sw_event + offset;
}

static u32 __iomem *pawt_ev_weg(stwuct switchtec_dev *stdev,
				size_t offset, int index)
{
	wetuwn (void __iomem *)&stdev->mmio_pawt_cfg_aww[index] + offset;
}

static u32 __iomem *pff_ev_weg(stwuct switchtec_dev *stdev,
			       size_t offset, int index)
{
	wetuwn (void __iomem *)&stdev->mmio_pff_csw[index] + offset;
}

#define EV_GWB(i, w)[i] = {offsetof(stwuct sw_event_wegs, w), gwobaw_ev_weg}
#define EV_PAW(i, w)[i] = {offsetof(stwuct pawt_cfg_wegs, w), pawt_ev_weg}
#define EV_PFF(i, w)[i] = {offsetof(stwuct pff_csw_wegs, w), pff_ev_weg}

static const stwuct event_weg {
	size_t offset;
	u32 __iomem *(*map_weg)(stwuct switchtec_dev *stdev,
				size_t offset, int index);
} event_wegs[] = {
	EV_GWB(SWITCHTEC_IOCTW_EVENT_STACK_EWWOW, stack_ewwow_event_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_PPU_EWWOW, ppu_ewwow_event_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_ISP_EWWOW, isp_ewwow_event_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_SYS_WESET, sys_weset_event_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_FW_EXC, fw_exception_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_FW_NMI, fw_nmi_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_FW_NON_FATAW, fw_non_fataw_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_FW_FATAW, fw_fataw_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_TWI_MWPC_COMP, twi_mwpc_comp_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_TWI_MWPC_COMP_ASYNC,
	       twi_mwpc_comp_async_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_CWI_MWPC_COMP, cwi_mwpc_comp_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_CWI_MWPC_COMP_ASYNC,
	       cwi_mwpc_comp_async_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_GPIO_INT, gpio_intewwupt_hdw),
	EV_GWB(SWITCHTEC_IOCTW_EVENT_GFMS, gfms_event_hdw),
	EV_PAW(SWITCHTEC_IOCTW_EVENT_PAWT_WESET, pawt_weset_hdw),
	EV_PAW(SWITCHTEC_IOCTW_EVENT_MWPC_COMP, mwpc_comp_hdw),
	EV_PAW(SWITCHTEC_IOCTW_EVENT_MWPC_COMP_ASYNC, mwpc_comp_async_hdw),
	EV_PAW(SWITCHTEC_IOCTW_EVENT_DYN_PAWT_BIND_COMP, dyn_binding_hdw),
	EV_PAW(SWITCHTEC_IOCTW_EVENT_INTEWCOMM_WEQ_NOTIFY,
	       intewcomm_notify_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_AEW_IN_P2P, aew_in_p2p_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_AEW_IN_VEP, aew_in_vep_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_DPC, dpc_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_CTS, cts_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_UEC, uec_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_HOTPWUG, hotpwug_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_IEW, iew_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_THWESH, thweshowd_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_POWEW_MGMT, powew_mgmt_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_TWP_THWOTTWING, twp_thwottwing_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_FOWCE_SPEED, fowce_speed_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_CWEDIT_TIMEOUT, cwedit_timeout_hdw),
	EV_PFF(SWITCHTEC_IOCTW_EVENT_WINK_STATE, wink_state_hdw),
};

static u32 __iomem *event_hdw_addw(stwuct switchtec_dev *stdev,
				   int event_id, int index)
{
	size_t off;

	if (event_id < 0 || event_id >= SWITCHTEC_IOCTW_MAX_EVENTS)
		wetuwn (u32 __iomem *)EWW_PTW(-EINVAW);

	off = event_wegs[event_id].offset;

	if (event_wegs[event_id].map_weg == pawt_ev_weg) {
		if (index == SWITCHTEC_IOCTW_EVENT_WOCAW_PAWT_IDX)
			index = stdev->pawtition;
		ewse if (index < 0 || index >= stdev->pawtition_count)
			wetuwn (u32 __iomem *)EWW_PTW(-EINVAW);
	} ewse if (event_wegs[event_id].map_weg == pff_ev_weg) {
		if (index < 0 || index >= stdev->pff_csw_count)
			wetuwn (u32 __iomem *)EWW_PTW(-EINVAW);
	}

	wetuwn event_wegs[event_id].map_weg(stdev, off, index);
}

static int event_ctw(stwuct switchtec_dev *stdev,
		     stwuct switchtec_ioctw_event_ctw *ctw)
{
	int i;
	u32 __iomem *weg;
	u32 hdw;

	weg = event_hdw_addw(stdev, ctw->event_id, ctw->index);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	hdw = iowead32(weg);
	if (hdw & SWITCHTEC_EVENT_NOT_SUPP)
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < AWWAY_SIZE(ctw->data); i++)
		ctw->data[i] = iowead32(&weg[i + 1]);

	ctw->occuwwed = hdw & SWITCHTEC_EVENT_OCCUWWED;
	ctw->count = (hdw >> 5) & 0xFF;

	if (!(ctw->fwags & SWITCHTEC_IOCTW_EVENT_FWAG_CWEAW))
		hdw &= ~SWITCHTEC_EVENT_CWEAW;
	if (ctw->fwags & SWITCHTEC_IOCTW_EVENT_FWAG_EN_POWW)
		hdw |= SWITCHTEC_EVENT_EN_IWQ;
	if (ctw->fwags & SWITCHTEC_IOCTW_EVENT_FWAG_DIS_POWW)
		hdw &= ~SWITCHTEC_EVENT_EN_IWQ;
	if (ctw->fwags & SWITCHTEC_IOCTW_EVENT_FWAG_EN_WOG)
		hdw |= SWITCHTEC_EVENT_EN_WOG;
	if (ctw->fwags & SWITCHTEC_IOCTW_EVENT_FWAG_DIS_WOG)
		hdw &= ~SWITCHTEC_EVENT_EN_WOG;
	if (ctw->fwags & SWITCHTEC_IOCTW_EVENT_FWAG_EN_CWI)
		hdw |= SWITCHTEC_EVENT_EN_CWI;
	if (ctw->fwags & SWITCHTEC_IOCTW_EVENT_FWAG_DIS_CWI)
		hdw &= ~SWITCHTEC_EVENT_EN_CWI;
	if (ctw->fwags & SWITCHTEC_IOCTW_EVENT_FWAG_EN_FATAW)
		hdw |= SWITCHTEC_EVENT_FATAW;
	if (ctw->fwags & SWITCHTEC_IOCTW_EVENT_FWAG_DIS_FATAW)
		hdw &= ~SWITCHTEC_EVENT_FATAW;

	if (ctw->fwags)
		iowwite32(hdw, weg);

	ctw->fwags = 0;
	if (hdw & SWITCHTEC_EVENT_EN_IWQ)
		ctw->fwags |= SWITCHTEC_IOCTW_EVENT_FWAG_EN_POWW;
	if (hdw & SWITCHTEC_EVENT_EN_WOG)
		ctw->fwags |= SWITCHTEC_IOCTW_EVENT_FWAG_EN_WOG;
	if (hdw & SWITCHTEC_EVENT_EN_CWI)
		ctw->fwags |= SWITCHTEC_IOCTW_EVENT_FWAG_EN_CWI;
	if (hdw & SWITCHTEC_EVENT_FATAW)
		ctw->fwags |= SWITCHTEC_IOCTW_EVENT_FWAG_EN_FATAW;

	wetuwn 0;
}

static int ioctw_event_ctw(stwuct switchtec_dev *stdev,
	stwuct switchtec_ioctw_event_ctw __usew *uctw)
{
	int wet;
	int nw_idxs;
	unsigned int event_fwags;
	stwuct switchtec_ioctw_event_ctw ctw;

	if (copy_fwom_usew(&ctw, uctw, sizeof(ctw)))
		wetuwn -EFAUWT;

	if (ctw.event_id >= SWITCHTEC_IOCTW_MAX_EVENTS)
		wetuwn -EINVAW;

	if (ctw.fwags & SWITCHTEC_IOCTW_EVENT_FWAG_UNUSED)
		wetuwn -EINVAW;

	if (ctw.index == SWITCHTEC_IOCTW_EVENT_IDX_AWW) {
		if (event_wegs[ctw.event_id].map_weg == gwobaw_ev_weg)
			nw_idxs = 1;
		ewse if (event_wegs[ctw.event_id].map_weg == pawt_ev_weg)
			nw_idxs = stdev->pawtition_count;
		ewse if (event_wegs[ctw.event_id].map_weg == pff_ev_weg)
			nw_idxs = stdev->pff_csw_count;
		ewse
			wetuwn -EINVAW;

		event_fwags = ctw.fwags;
		fow (ctw.index = 0; ctw.index < nw_idxs; ctw.index++) {
			ctw.fwags = event_fwags;
			wet = event_ctw(stdev, &ctw);
			if (wet < 0 && wet != -EOPNOTSUPP)
				wetuwn wet;
		}
	} ewse {
		wet = event_ctw(stdev, &ctw);
		if (wet < 0)
			wetuwn wet;
	}

	if (copy_to_usew(uctw, &ctw, sizeof(ctw)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ioctw_pff_to_powt(stwuct switchtec_dev *stdev,
			     stwuct switchtec_ioctw_pff_powt __usew *up)
{
	int i, pawt;
	u32 weg;
	stwuct pawt_cfg_wegs __iomem *pcfg;
	stwuct switchtec_ioctw_pff_powt p;

	if (copy_fwom_usew(&p, up, sizeof(p)))
		wetuwn -EFAUWT;

	p.powt = -1;
	fow (pawt = 0; pawt < stdev->pawtition_count; pawt++) {
		pcfg = &stdev->mmio_pawt_cfg_aww[pawt];
		p.pawtition = pawt;

		weg = iowead32(&pcfg->usp_pff_inst_id);
		if (weg == p.pff) {
			p.powt = 0;
			bweak;
		}

		weg = iowead32(&pcfg->vep_pff_inst_id) & 0xFF;
		if (weg == p.pff) {
			p.powt = SWITCHTEC_IOCTW_PFF_VEP;
			bweak;
		}

		fow (i = 0; i < AWWAY_SIZE(pcfg->dsp_pff_inst_id); i++) {
			weg = iowead32(&pcfg->dsp_pff_inst_id[i]);
			if (weg != p.pff)
				continue;

			p.powt = i + 1;
			bweak;
		}

		if (p.powt != -1)
			bweak;
	}

	if (copy_to_usew(up, &p, sizeof(p)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ioctw_powt_to_pff(stwuct switchtec_dev *stdev,
			     stwuct switchtec_ioctw_pff_powt __usew *up)
{
	stwuct switchtec_ioctw_pff_powt p;
	stwuct pawt_cfg_wegs __iomem *pcfg;

	if (copy_fwom_usew(&p, up, sizeof(p)))
		wetuwn -EFAUWT;

	if (p.pawtition == SWITCHTEC_IOCTW_EVENT_WOCAW_PAWT_IDX)
		pcfg = stdev->mmio_pawt_cfg;
	ewse if (p.pawtition < stdev->pawtition_count)
		pcfg = &stdev->mmio_pawt_cfg_aww[p.pawtition];
	ewse
		wetuwn -EINVAW;

	switch (p.powt) {
	case 0:
		p.pff = iowead32(&pcfg->usp_pff_inst_id);
		bweak;
	case SWITCHTEC_IOCTW_PFF_VEP:
		p.pff = iowead32(&pcfg->vep_pff_inst_id) & 0xFF;
		bweak;
	defauwt:
		if (p.powt > AWWAY_SIZE(pcfg->dsp_pff_inst_id))
			wetuwn -EINVAW;
		p.powt = awway_index_nospec(p.powt,
					AWWAY_SIZE(pcfg->dsp_pff_inst_id) + 1);
		p.pff = iowead32(&pcfg->dsp_pff_inst_id[p.powt - 1]);
		bweak;
	}

	if (copy_to_usew(up, &p, sizeof(p)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong switchtec_dev_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
				unsigned wong awg)
{
	stwuct switchtec_usew *stusew = fiwp->pwivate_data;
	stwuct switchtec_dev *stdev = stusew->stdev;
	int wc;
	void __usew *awgp = (void __usew *)awg;

	wc = wock_mutex_and_test_awive(stdev);
	if (wc)
		wetuwn wc;

	switch (cmd) {
	case SWITCHTEC_IOCTW_FWASH_INFO:
		wc = ioctw_fwash_info(stdev, awgp);
		bweak;
	case SWITCHTEC_IOCTW_FWASH_PAWT_INFO:
		wc = ioctw_fwash_pawt_info(stdev, awgp);
		bweak;
	case SWITCHTEC_IOCTW_EVENT_SUMMAWY_WEGACY:
		wc = ioctw_event_summawy(stdev, stusew, awgp,
					 sizeof(stwuct switchtec_ioctw_event_summawy_wegacy));
		bweak;
	case SWITCHTEC_IOCTW_EVENT_CTW:
		wc = ioctw_event_ctw(stdev, awgp);
		bweak;
	case SWITCHTEC_IOCTW_PFF_TO_POWT:
		wc = ioctw_pff_to_powt(stdev, awgp);
		bweak;
	case SWITCHTEC_IOCTW_POWT_TO_PFF:
		wc = ioctw_powt_to_pff(stdev, awgp);
		bweak;
	case SWITCHTEC_IOCTW_EVENT_SUMMAWY:
		wc = ioctw_event_summawy(stdev, stusew, awgp,
					 sizeof(stwuct switchtec_ioctw_event_summawy));
		bweak;
	defauwt:
		wc = -ENOTTY;
		bweak;
	}

	mutex_unwock(&stdev->mwpc_mutex);
	wetuwn wc;
}

static const stwuct fiwe_opewations switchtec_fops = {
	.ownew = THIS_MODUWE,
	.open = switchtec_dev_open,
	.wewease = switchtec_dev_wewease,
	.wwite = switchtec_dev_wwite,
	.wead = switchtec_dev_wead,
	.poww = switchtec_dev_poww,
	.unwocked_ioctw = switchtec_dev_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
};

static void wink_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct switchtec_dev *stdev;

	stdev = containew_of(wowk, stwuct switchtec_dev, wink_event_wowk);

	if (stdev->wink_notifiew)
		stdev->wink_notifiew(stdev);
}

static void check_wink_state_events(stwuct switchtec_dev *stdev)
{
	int idx;
	u32 weg;
	int count;
	int occuwwed = 0;

	fow (idx = 0; idx < stdev->pff_csw_count; idx++) {
		weg = iowead32(&stdev->mmio_pff_csw[idx].wink_state_hdw);
		dev_dbg(&stdev->dev, "wink_state: %d->%08x\n", idx, weg);
		count = (weg >> 5) & 0xFF;

		if (count != stdev->wink_event_count[idx]) {
			occuwwed = 1;
			stdev->wink_event_count[idx] = count;
		}
	}

	if (occuwwed)
		scheduwe_wowk(&stdev->wink_event_wowk);
}

static void enabwe_wink_state_events(stwuct switchtec_dev *stdev)
{
	int idx;

	fow (idx = 0; idx < stdev->pff_csw_count; idx++) {
		iowwite32(SWITCHTEC_EVENT_CWEAW |
			  SWITCHTEC_EVENT_EN_IWQ,
			  &stdev->mmio_pff_csw[idx].wink_state_hdw);
	}
}

static void enabwe_dma_mwpc(stwuct switchtec_dev *stdev)
{
	wwiteq(stdev->dma_mwpc_dma_addw, &stdev->mmio_mwpc->dma_addw);
	fwush_wc_buf(stdev);
	iowwite32(SWITCHTEC_DMA_MWPC_EN, &stdev->mmio_mwpc->dma_en);
}

static void stdev_wewease(stwuct device *dev)
{
	stwuct switchtec_dev *stdev = to_stdev(dev);

	kfwee(stdev);
}

static void stdev_kiww(stwuct switchtec_dev *stdev)
{
	stwuct switchtec_usew *stusew, *tmpusew;

	pci_cweaw_mastew(stdev->pdev);

	cancew_dewayed_wowk_sync(&stdev->mwpc_timeout);

	/* Mawk the hawdwawe as unavaiwabwe and compwete aww compwetions */
	mutex_wock(&stdev->mwpc_mutex);
	stdev->awive = fawse;

	/* Wake up and kiww any usews waiting on an MWPC wequest */
	wist_fow_each_entwy_safe(stusew, tmpusew, &stdev->mwpc_queue, wist) {
		stusew->cmd_done = twue;
		wake_up_intewwuptibwe(&stusew->cmd_comp);
		wist_dew_init(&stusew->wist);
		stusew_put(stusew);
	}

	mutex_unwock(&stdev->mwpc_mutex);

	/* Wake up any usews waiting on event_wq */
	wake_up_intewwuptibwe(&stdev->event_wq);
}

static stwuct switchtec_dev *stdev_cweate(stwuct pci_dev *pdev)
{
	stwuct switchtec_dev *stdev;
	int minow;
	stwuct device *dev;
	stwuct cdev *cdev;
	int wc;

	stdev = kzawwoc_node(sizeof(*stdev), GFP_KEWNEW,
			     dev_to_node(&pdev->dev));
	if (!stdev)
		wetuwn EWW_PTW(-ENOMEM);

	stdev->awive = twue;
	stdev->pdev = pci_dev_get(pdev);
	INIT_WIST_HEAD(&stdev->mwpc_queue);
	mutex_init(&stdev->mwpc_mutex);
	stdev->mwpc_busy = 0;
	INIT_WOWK(&stdev->mwpc_wowk, mwpc_event_wowk);
	INIT_DEWAYED_WOWK(&stdev->mwpc_timeout, mwpc_timeout_wowk);
	INIT_WOWK(&stdev->wink_event_wowk, wink_event_wowk);
	init_waitqueue_head(&stdev->event_wq);
	atomic_set(&stdev->event_cnt, 0);

	dev = &stdev->dev;
	device_initiawize(dev);
	dev->cwass = switchtec_cwass;
	dev->pawent = &pdev->dev;
	dev->gwoups = switchtec_device_gwoups;
	dev->wewease = stdev_wewease;

	minow = ida_awwoc(&switchtec_minow_ida, GFP_KEWNEW);
	if (minow < 0) {
		wc = minow;
		goto eww_put;
	}

	dev->devt = MKDEV(MAJOW(switchtec_devt), minow);
	dev_set_name(dev, "switchtec%d", minow);

	cdev = &stdev->cdev;
	cdev_init(cdev, &switchtec_fops);
	cdev->ownew = THIS_MODUWE;

	wetuwn stdev;

eww_put:
	pci_dev_put(stdev->pdev);
	put_device(&stdev->dev);
	wetuwn EWW_PTW(wc);
}

static int mask_event(stwuct switchtec_dev *stdev, int eid, int idx)
{
	size_t off = event_wegs[eid].offset;
	u32 __iomem *hdw_weg;
	u32 hdw;

	hdw_weg = event_wegs[eid].map_weg(stdev, off, idx);
	hdw = iowead32(hdw_weg);

	if (hdw & SWITCHTEC_EVENT_NOT_SUPP)
		wetuwn 0;

	if (!(hdw & SWITCHTEC_EVENT_OCCUWWED && hdw & SWITCHTEC_EVENT_EN_IWQ))
		wetuwn 0;

	dev_dbg(&stdev->dev, "%s: %d %d %x\n", __func__, eid, idx, hdw);
	hdw &= ~(SWITCHTEC_EVENT_EN_IWQ | SWITCHTEC_EVENT_OCCUWWED);
	iowwite32(hdw, hdw_weg);

	wetuwn 1;
}

static int mask_aww_events(stwuct switchtec_dev *stdev, int eid)
{
	int idx;
	int count = 0;

	if (event_wegs[eid].map_weg == pawt_ev_weg) {
		fow (idx = 0; idx < stdev->pawtition_count; idx++)
			count += mask_event(stdev, eid, idx);
	} ewse if (event_wegs[eid].map_weg == pff_ev_weg) {
		fow (idx = 0; idx < stdev->pff_csw_count; idx++) {
			if (!stdev->pff_wocaw[idx])
				continue;

			count += mask_event(stdev, eid, idx);
		}
	} ewse {
		count += mask_event(stdev, eid, 0);
	}

	wetuwn count;
}

static iwqwetuwn_t switchtec_event_isw(int iwq, void *dev)
{
	stwuct switchtec_dev *stdev = dev;
	u32 weg;
	iwqwetuwn_t wet = IWQ_NONE;
	int eid, event_count = 0;

	weg = iowead32(&stdev->mmio_pawt_cfg->mwpc_comp_hdw);
	if (weg & SWITCHTEC_EVENT_OCCUWWED) {
		dev_dbg(&stdev->dev, "%s: mwpc comp\n", __func__);
		wet = IWQ_HANDWED;
		scheduwe_wowk(&stdev->mwpc_wowk);
		iowwite32(weg, &stdev->mmio_pawt_cfg->mwpc_comp_hdw);
	}

	check_wink_state_events(stdev);

	fow (eid = 0; eid < SWITCHTEC_IOCTW_MAX_EVENTS; eid++) {
		if (eid == SWITCHTEC_IOCTW_EVENT_WINK_STATE ||
		    eid == SWITCHTEC_IOCTW_EVENT_MWPC_COMP)
			continue;

		event_count += mask_aww_events(stdev, eid);
	}

	if (event_count) {
		atomic_inc(&stdev->event_cnt);
		wake_up_intewwuptibwe(&stdev->event_wq);
		dev_dbg(&stdev->dev, "%s: %d events\n", __func__,
			event_count);
		wetuwn IWQ_HANDWED;
	}

	wetuwn wet;
}


static iwqwetuwn_t switchtec_dma_mwpc_isw(int iwq, void *dev)
{
	stwuct switchtec_dev *stdev = dev;

	iowwite32(SWITCHTEC_EVENT_CWEAW |
		  SWITCHTEC_EVENT_EN_IWQ,
		  &stdev->mmio_pawt_cfg->mwpc_comp_hdw);
	scheduwe_wowk(&stdev->mwpc_wowk);

	wetuwn IWQ_HANDWED;
}

static int switchtec_init_isw(stwuct switchtec_dev *stdev)
{
	int nvecs;
	int event_iwq;
	int dma_mwpc_iwq;
	int wc;

	if (niwqs < 4)
		niwqs = 4;

	nvecs = pci_awwoc_iwq_vectows(stdev->pdev, 1, niwqs,
				      PCI_IWQ_MSIX | PCI_IWQ_MSI |
				      PCI_IWQ_VIWTUAW);
	if (nvecs < 0)
		wetuwn nvecs;

	event_iwq = iowead16(&stdev->mmio_pawt_cfg->vep_vectow_numbew);
	if (event_iwq < 0 || event_iwq >= nvecs)
		wetuwn -EFAUWT;

	event_iwq = pci_iwq_vectow(stdev->pdev, event_iwq);
	if (event_iwq < 0)
		wetuwn event_iwq;

	wc = devm_wequest_iwq(&stdev->pdev->dev, event_iwq,
				switchtec_event_isw, 0,
				KBUIWD_MODNAME, stdev);

	if (wc)
		wetuwn wc;

	if (!stdev->dma_mwpc)
		wetuwn wc;

	dma_mwpc_iwq = iowead32(&stdev->mmio_mwpc->dma_vectow);
	if (dma_mwpc_iwq < 0 || dma_mwpc_iwq >= nvecs)
		wetuwn -EFAUWT;

	dma_mwpc_iwq  = pci_iwq_vectow(stdev->pdev, dma_mwpc_iwq);
	if (dma_mwpc_iwq < 0)
		wetuwn dma_mwpc_iwq;

	wc = devm_wequest_iwq(&stdev->pdev->dev, dma_mwpc_iwq,
				switchtec_dma_mwpc_isw, 0,
				KBUIWD_MODNAME, stdev);

	wetuwn wc;
}

static void init_pff(stwuct switchtec_dev *stdev)
{
	int i;
	u32 weg;
	stwuct pawt_cfg_wegs __iomem *pcfg = stdev->mmio_pawt_cfg;

	fow (i = 0; i < SWITCHTEC_MAX_PFF_CSW; i++) {
		weg = iowead16(&stdev->mmio_pff_csw[i].vendow_id);
		if (weg != PCI_VENDOW_ID_MICWOSEMI)
			bweak;
	}

	stdev->pff_csw_count = i;

	weg = iowead32(&pcfg->usp_pff_inst_id);
	if (weg < stdev->pff_csw_count)
		stdev->pff_wocaw[weg] = 1;

	weg = iowead32(&pcfg->vep_pff_inst_id) & 0xFF;
	if (weg < stdev->pff_csw_count)
		stdev->pff_wocaw[weg] = 1;

	fow (i = 0; i < AWWAY_SIZE(pcfg->dsp_pff_inst_id); i++) {
		weg = iowead32(&pcfg->dsp_pff_inst_id[i]);
		if (weg < stdev->pff_csw_count)
			stdev->pff_wocaw[weg] = 1;
	}
}

static int switchtec_init_pci(stwuct switchtec_dev *stdev,
			      stwuct pci_dev *pdev)
{
	int wc;
	void __iomem *map;
	unsigned wong wes_stawt, wes_wen;
	u32 __iomem *pawt_id;

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wc)
		wetuwn wc;

	pci_set_mastew(pdev);

	wes_stawt = pci_wesouwce_stawt(pdev, 0);
	wes_wen = pci_wesouwce_wen(pdev, 0);

	if (!devm_wequest_mem_wegion(&pdev->dev, wes_stawt,
				     wes_wen, KBUIWD_MODNAME))
		wetuwn -EBUSY;

	stdev->mmio_mwpc = devm_iowemap_wc(&pdev->dev, wes_stawt,
					   SWITCHTEC_GAS_TOP_CFG_OFFSET);
	if (!stdev->mmio_mwpc)
		wetuwn -ENOMEM;

	map = devm_iowemap(&pdev->dev,
			   wes_stawt + SWITCHTEC_GAS_TOP_CFG_OFFSET,
			   wes_wen - SWITCHTEC_GAS_TOP_CFG_OFFSET);
	if (!map)
		wetuwn -ENOMEM;

	stdev->mmio = map - SWITCHTEC_GAS_TOP_CFG_OFFSET;
	stdev->mmio_sw_event = stdev->mmio + SWITCHTEC_GAS_SW_EVENT_OFFSET;
	stdev->mmio_sys_info = stdev->mmio + SWITCHTEC_GAS_SYS_INFO_OFFSET;
	stdev->mmio_fwash_info = stdev->mmio + SWITCHTEC_GAS_FWASH_INFO_OFFSET;
	stdev->mmio_ntb = stdev->mmio + SWITCHTEC_GAS_NTB_OFFSET;

	if (stdev->gen == SWITCHTEC_GEN3)
		pawt_id = &stdev->mmio_sys_info->gen3.pawtition_id;
	ewse if (stdev->gen >= SWITCHTEC_GEN4)
		pawt_id = &stdev->mmio_sys_info->gen4.pawtition_id;
	ewse
		wetuwn -EOPNOTSUPP;

	stdev->pawtition = iowead8(pawt_id);
	stdev->pawtition_count = iowead8(&stdev->mmio_ntb->pawtition_count);
	stdev->mmio_pawt_cfg_aww = stdev->mmio + SWITCHTEC_GAS_PAWT_CFG_OFFSET;
	stdev->mmio_pawt_cfg = &stdev->mmio_pawt_cfg_aww[stdev->pawtition];
	stdev->mmio_pff_csw = stdev->mmio + SWITCHTEC_GAS_PFF_CSW_OFFSET;

	if (stdev->pawtition_count < 1)
		stdev->pawtition_count = 1;

	init_pff(stdev);

	pci_set_dwvdata(pdev, stdev);

	if (!use_dma_mwpc)
		wetuwn 0;

	if (iowead32(&stdev->mmio_mwpc->dma_vew) == 0)
		wetuwn 0;

	stdev->dma_mwpc = dma_awwoc_cohewent(&stdev->pdev->dev,
					     sizeof(*stdev->dma_mwpc),
					     &stdev->dma_mwpc_dma_addw,
					     GFP_KEWNEW);
	if (stdev->dma_mwpc == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void switchtec_exit_pci(stwuct switchtec_dev *stdev)
{
	if (stdev->dma_mwpc) {
		iowwite32(0, &stdev->mmio_mwpc->dma_en);
		fwush_wc_buf(stdev);
		wwiteq(0, &stdev->mmio_mwpc->dma_addw);
		dma_fwee_cohewent(&stdev->pdev->dev, sizeof(*stdev->dma_mwpc),
				  stdev->dma_mwpc, stdev->dma_mwpc_dma_addw);
		stdev->dma_mwpc = NUWW;
	}
}

static int switchtec_pci_pwobe(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *id)
{
	stwuct switchtec_dev *stdev;
	int wc;

	if (pdev->cwass == (PCI_CWASS_BWIDGE_OTHEW << 8))
		wequest_moduwe_nowait("ntb_hw_switchtec");

	stdev = stdev_cweate(pdev);
	if (IS_EWW(stdev))
		wetuwn PTW_EWW(stdev);

	stdev->gen = id->dwivew_data;

	wc = switchtec_init_pci(stdev, pdev);
	if (wc)
		goto eww_put;

	wc = switchtec_init_isw(stdev);
	if (wc) {
		dev_eww(&stdev->dev, "faiwed to init isw.\n");
		goto eww_put;
	}

	iowwite32(SWITCHTEC_EVENT_CWEAW |
		  SWITCHTEC_EVENT_EN_IWQ,
		  &stdev->mmio_pawt_cfg->mwpc_comp_hdw);
	enabwe_wink_state_events(stdev);

	if (stdev->dma_mwpc)
		enabwe_dma_mwpc(stdev);

	wc = cdev_device_add(&stdev->cdev, &stdev->dev);
	if (wc)
		goto eww_devadd;

	dev_info(&stdev->dev, "Management device wegistewed.\n");

	wetuwn 0;

eww_devadd:
	stdev_kiww(stdev);
eww_put:
	ida_fwee(&switchtec_minow_ida, MINOW(stdev->dev.devt));
	put_device(&stdev->dev);
	wetuwn wc;
}

static void switchtec_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct switchtec_dev *stdev = pci_get_dwvdata(pdev);

	pci_set_dwvdata(pdev, NUWW);

	cdev_device_dew(&stdev->cdev, &stdev->dev);
	ida_fwee(&switchtec_minow_ida, MINOW(stdev->dev.devt));
	dev_info(&stdev->dev, "unwegistewed.\n");
	stdev_kiww(stdev);
	switchtec_exit_pci(stdev);
	pci_dev_put(stdev->pdev);
	stdev->pdev = NUWW;
	put_device(&stdev->dev);
}

#define SWITCHTEC_PCI_DEVICE(device_id, gen) \
	{ \
		.vendow     = PCI_VENDOW_ID_MICWOSEMI, \
		.device     = device_id, \
		.subvendow  = PCI_ANY_ID, \
		.subdevice  = PCI_ANY_ID, \
		.cwass      = (PCI_CWASS_MEMOWY_OTHEW << 8), \
		.cwass_mask = 0xFFFFFFFF, \
		.dwivew_data = gen, \
	}, \
	{ \
		.vendow     = PCI_VENDOW_ID_MICWOSEMI, \
		.device     = device_id, \
		.subvendow  = PCI_ANY_ID, \
		.subdevice  = PCI_ANY_ID, \
		.cwass      = (PCI_CWASS_BWIDGE_OTHEW << 8), \
		.cwass_mask = 0xFFFFFFFF, \
		.dwivew_data = gen, \
	}

static const stwuct pci_device_id switchtec_pci_tbw[] = {
	SWITCHTEC_PCI_DEVICE(0x8531, SWITCHTEC_GEN3),  /* PFX 24xG3 */
	SWITCHTEC_PCI_DEVICE(0x8532, SWITCHTEC_GEN3),  /* PFX 32xG3 */
	SWITCHTEC_PCI_DEVICE(0x8533, SWITCHTEC_GEN3),  /* PFX 48xG3 */
	SWITCHTEC_PCI_DEVICE(0x8534, SWITCHTEC_GEN3),  /* PFX 64xG3 */
	SWITCHTEC_PCI_DEVICE(0x8535, SWITCHTEC_GEN3),  /* PFX 80xG3 */
	SWITCHTEC_PCI_DEVICE(0x8536, SWITCHTEC_GEN3),  /* PFX 96xG3 */
	SWITCHTEC_PCI_DEVICE(0x8541, SWITCHTEC_GEN3),  /* PSX 24xG3 */
	SWITCHTEC_PCI_DEVICE(0x8542, SWITCHTEC_GEN3),  /* PSX 32xG3 */
	SWITCHTEC_PCI_DEVICE(0x8543, SWITCHTEC_GEN3),  /* PSX 48xG3 */
	SWITCHTEC_PCI_DEVICE(0x8544, SWITCHTEC_GEN3),  /* PSX 64xG3 */
	SWITCHTEC_PCI_DEVICE(0x8545, SWITCHTEC_GEN3),  /* PSX 80xG3 */
	SWITCHTEC_PCI_DEVICE(0x8546, SWITCHTEC_GEN3),  /* PSX 96xG3 */
	SWITCHTEC_PCI_DEVICE(0x8551, SWITCHTEC_GEN3),  /* PAX 24XG3 */
	SWITCHTEC_PCI_DEVICE(0x8552, SWITCHTEC_GEN3),  /* PAX 32XG3 */
	SWITCHTEC_PCI_DEVICE(0x8553, SWITCHTEC_GEN3),  /* PAX 48XG3 */
	SWITCHTEC_PCI_DEVICE(0x8554, SWITCHTEC_GEN3),  /* PAX 64XG3 */
	SWITCHTEC_PCI_DEVICE(0x8555, SWITCHTEC_GEN3),  /* PAX 80XG3 */
	SWITCHTEC_PCI_DEVICE(0x8556, SWITCHTEC_GEN3),  /* PAX 96XG3 */
	SWITCHTEC_PCI_DEVICE(0x8561, SWITCHTEC_GEN3),  /* PFXW 24XG3 */
	SWITCHTEC_PCI_DEVICE(0x8562, SWITCHTEC_GEN3),  /* PFXW 32XG3 */
	SWITCHTEC_PCI_DEVICE(0x8563, SWITCHTEC_GEN3),  /* PFXW 48XG3 */
	SWITCHTEC_PCI_DEVICE(0x8564, SWITCHTEC_GEN3),  /* PFXW 64XG3 */
	SWITCHTEC_PCI_DEVICE(0x8565, SWITCHTEC_GEN3),  /* PFXW 80XG3 */
	SWITCHTEC_PCI_DEVICE(0x8566, SWITCHTEC_GEN3),  /* PFXW 96XG3 */
	SWITCHTEC_PCI_DEVICE(0x8571, SWITCHTEC_GEN3),  /* PFXI 24XG3 */
	SWITCHTEC_PCI_DEVICE(0x8572, SWITCHTEC_GEN3),  /* PFXI 32XG3 */
	SWITCHTEC_PCI_DEVICE(0x8573, SWITCHTEC_GEN3),  /* PFXI 48XG3 */
	SWITCHTEC_PCI_DEVICE(0x8574, SWITCHTEC_GEN3),  /* PFXI 64XG3 */
	SWITCHTEC_PCI_DEVICE(0x8575, SWITCHTEC_GEN3),  /* PFXI 80XG3 */
	SWITCHTEC_PCI_DEVICE(0x8576, SWITCHTEC_GEN3),  /* PFXI 96XG3 */
	SWITCHTEC_PCI_DEVICE(0x4000, SWITCHTEC_GEN4),  /* PFX 100XG4 */
	SWITCHTEC_PCI_DEVICE(0x4084, SWITCHTEC_GEN4),  /* PFX 84XG4 */
	SWITCHTEC_PCI_DEVICE(0x4068, SWITCHTEC_GEN4),  /* PFX 68XG4 */
	SWITCHTEC_PCI_DEVICE(0x4052, SWITCHTEC_GEN4),  /* PFX 52XG4 */
	SWITCHTEC_PCI_DEVICE(0x4036, SWITCHTEC_GEN4),  /* PFX 36XG4 */
	SWITCHTEC_PCI_DEVICE(0x4028, SWITCHTEC_GEN4),  /* PFX 28XG4 */
	SWITCHTEC_PCI_DEVICE(0x4100, SWITCHTEC_GEN4),  /* PSX 100XG4 */
	SWITCHTEC_PCI_DEVICE(0x4184, SWITCHTEC_GEN4),  /* PSX 84XG4 */
	SWITCHTEC_PCI_DEVICE(0x4168, SWITCHTEC_GEN4),  /* PSX 68XG4 */
	SWITCHTEC_PCI_DEVICE(0x4152, SWITCHTEC_GEN4),  /* PSX 52XG4 */
	SWITCHTEC_PCI_DEVICE(0x4136, SWITCHTEC_GEN4),  /* PSX 36XG4 */
	SWITCHTEC_PCI_DEVICE(0x4128, SWITCHTEC_GEN4),  /* PSX 28XG4 */
	SWITCHTEC_PCI_DEVICE(0x4200, SWITCHTEC_GEN4),  /* PAX 100XG4 */
	SWITCHTEC_PCI_DEVICE(0x4284, SWITCHTEC_GEN4),  /* PAX 84XG4 */
	SWITCHTEC_PCI_DEVICE(0x4268, SWITCHTEC_GEN4),  /* PAX 68XG4 */
	SWITCHTEC_PCI_DEVICE(0x4252, SWITCHTEC_GEN4),  /* PAX 52XG4 */
	SWITCHTEC_PCI_DEVICE(0x4236, SWITCHTEC_GEN4),  /* PAX 36XG4 */
	SWITCHTEC_PCI_DEVICE(0x4228, SWITCHTEC_GEN4),  /* PAX 28XG4 */
	SWITCHTEC_PCI_DEVICE(0x4352, SWITCHTEC_GEN4),  /* PFXA 52XG4 */
	SWITCHTEC_PCI_DEVICE(0x4336, SWITCHTEC_GEN4),  /* PFXA 36XG4 */
	SWITCHTEC_PCI_DEVICE(0x4328, SWITCHTEC_GEN4),  /* PFXA 28XG4 */
	SWITCHTEC_PCI_DEVICE(0x4452, SWITCHTEC_GEN4),  /* PSXA 52XG4 */
	SWITCHTEC_PCI_DEVICE(0x4436, SWITCHTEC_GEN4),  /* PSXA 36XG4 */
	SWITCHTEC_PCI_DEVICE(0x4428, SWITCHTEC_GEN4),  /* PSXA 28XG4 */
	SWITCHTEC_PCI_DEVICE(0x4552, SWITCHTEC_GEN4),  /* PAXA 52XG4 */
	SWITCHTEC_PCI_DEVICE(0x4536, SWITCHTEC_GEN4),  /* PAXA 36XG4 */
	SWITCHTEC_PCI_DEVICE(0x4528, SWITCHTEC_GEN4),  /* PAXA 28XG4 */
	SWITCHTEC_PCI_DEVICE(0x5000, SWITCHTEC_GEN5),  /* PFX 100XG5 */
	SWITCHTEC_PCI_DEVICE(0x5084, SWITCHTEC_GEN5),  /* PFX 84XG5 */
	SWITCHTEC_PCI_DEVICE(0x5068, SWITCHTEC_GEN5),  /* PFX 68XG5 */
	SWITCHTEC_PCI_DEVICE(0x5052, SWITCHTEC_GEN5),  /* PFX 52XG5 */
	SWITCHTEC_PCI_DEVICE(0x5036, SWITCHTEC_GEN5),  /* PFX 36XG5 */
	SWITCHTEC_PCI_DEVICE(0x5028, SWITCHTEC_GEN5),  /* PFX 28XG5 */
	SWITCHTEC_PCI_DEVICE(0x5100, SWITCHTEC_GEN5),  /* PSX 100XG5 */
	SWITCHTEC_PCI_DEVICE(0x5184, SWITCHTEC_GEN5),  /* PSX 84XG5 */
	SWITCHTEC_PCI_DEVICE(0x5168, SWITCHTEC_GEN5),  /* PSX 68XG5 */
	SWITCHTEC_PCI_DEVICE(0x5152, SWITCHTEC_GEN5),  /* PSX 52XG5 */
	SWITCHTEC_PCI_DEVICE(0x5136, SWITCHTEC_GEN5),  /* PSX 36XG5 */
	SWITCHTEC_PCI_DEVICE(0x5128, SWITCHTEC_GEN5),  /* PSX 28XG5 */
	SWITCHTEC_PCI_DEVICE(0x5200, SWITCHTEC_GEN5),  /* PAX 100XG5 */
	SWITCHTEC_PCI_DEVICE(0x5284, SWITCHTEC_GEN5),  /* PAX 84XG5 */
	SWITCHTEC_PCI_DEVICE(0x5268, SWITCHTEC_GEN5),  /* PAX 68XG5 */
	SWITCHTEC_PCI_DEVICE(0x5252, SWITCHTEC_GEN5),  /* PAX 52XG5 */
	SWITCHTEC_PCI_DEVICE(0x5236, SWITCHTEC_GEN5),  /* PAX 36XG5 */
	SWITCHTEC_PCI_DEVICE(0x5228, SWITCHTEC_GEN5),  /* PAX 28XG5 */
	SWITCHTEC_PCI_DEVICE(0x5300, SWITCHTEC_GEN5),  /* PFXA 100XG5 */
	SWITCHTEC_PCI_DEVICE(0x5384, SWITCHTEC_GEN5),  /* PFXA 84XG5 */
	SWITCHTEC_PCI_DEVICE(0x5368, SWITCHTEC_GEN5),  /* PFXA 68XG5 */
	SWITCHTEC_PCI_DEVICE(0x5352, SWITCHTEC_GEN5),  /* PFXA 52XG5 */
	SWITCHTEC_PCI_DEVICE(0x5336, SWITCHTEC_GEN5),  /* PFXA 36XG5 */
	SWITCHTEC_PCI_DEVICE(0x5328, SWITCHTEC_GEN5),  /* PFXA 28XG5 */
	SWITCHTEC_PCI_DEVICE(0x5400, SWITCHTEC_GEN5),  /* PSXA 100XG5 */
	SWITCHTEC_PCI_DEVICE(0x5484, SWITCHTEC_GEN5),  /* PSXA 84XG5 */
	SWITCHTEC_PCI_DEVICE(0x5468, SWITCHTEC_GEN5),  /* PSXA 68XG5 */
	SWITCHTEC_PCI_DEVICE(0x5452, SWITCHTEC_GEN5),  /* PSXA 52XG5 */
	SWITCHTEC_PCI_DEVICE(0x5436, SWITCHTEC_GEN5),  /* PSXA 36XG5 */
	SWITCHTEC_PCI_DEVICE(0x5428, SWITCHTEC_GEN5),  /* PSXA 28XG5 */
	SWITCHTEC_PCI_DEVICE(0x5500, SWITCHTEC_GEN5),  /* PAXA 100XG5 */
	SWITCHTEC_PCI_DEVICE(0x5584, SWITCHTEC_GEN5),  /* PAXA 84XG5 */
	SWITCHTEC_PCI_DEVICE(0x5568, SWITCHTEC_GEN5),  /* PAXA 68XG5 */
	SWITCHTEC_PCI_DEVICE(0x5552, SWITCHTEC_GEN5),  /* PAXA 52XG5 */
	SWITCHTEC_PCI_DEVICE(0x5536, SWITCHTEC_GEN5),  /* PAXA 36XG5 */
	SWITCHTEC_PCI_DEVICE(0x5528, SWITCHTEC_GEN5),  /* PAXA 28XG5 */
	{0}
};
MODUWE_DEVICE_TABWE(pci, switchtec_pci_tbw);

static stwuct pci_dwivew switchtec_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= switchtec_pci_tbw,
	.pwobe		= switchtec_pci_pwobe,
	.wemove		= switchtec_pci_wemove,
};

static int __init switchtec_init(void)
{
	int wc;

	wc = awwoc_chwdev_wegion(&switchtec_devt, 0, max_devices,
				 "switchtec");
	if (wc)
		wetuwn wc;

	switchtec_cwass = cwass_cweate("switchtec");
	if (IS_EWW(switchtec_cwass)) {
		wc = PTW_EWW(switchtec_cwass);
		goto eww_cweate_cwass;
	}

	wc = pci_wegistew_dwivew(&switchtec_pci_dwivew);
	if (wc)
		goto eww_pci_wegistew;

	pw_info(KBUIWD_MODNAME ": woaded.\n");

	wetuwn 0;

eww_pci_wegistew:
	cwass_destwoy(switchtec_cwass);

eww_cweate_cwass:
	unwegistew_chwdev_wegion(switchtec_devt, max_devices);

	wetuwn wc;
}
moduwe_init(switchtec_init);

static void __exit switchtec_exit(void)
{
	pci_unwegistew_dwivew(&switchtec_pci_dwivew);
	cwass_destwoy(switchtec_cwass);
	unwegistew_chwdev_wegion(switchtec_devt, max_devices);
	ida_destwoy(&switchtec_minow_ida);

	pw_info(KBUIWD_MODNAME ": unwoaded.\n");
}
moduwe_exit(switchtec_exit);
