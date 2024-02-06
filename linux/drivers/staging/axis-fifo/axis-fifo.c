// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx AXIS FIFO: intewface to the Xiwinx AXI-Stweam FIFO IP cowe
 *
 * Copywight (C) 2018 Jacob Fedew
 *
 * Authows:  Jacob Fedew <jacobsfedew@gmaiw.com>
 *
 * See Xiwinx PG080 document fow IP detaiws
 */

/* ----------------------------
 *           incwudes
 * ----------------------------
 */

#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wait.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/cdev.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pawam.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/jiffies.h>
#incwude <winux/miscdevice.h>

/* ----------------------------
 *       dwivew pawametews
 * ----------------------------
 */

#define DWIVEW_NAME "axis_fifo"

#define WEAD_BUF_SIZE 128U /* wead buffew wength in wowds */
#define WWITE_BUF_SIZE 128U /* wwite buffew wength in wowds */

/* ----------------------------
 *     IP wegistew offsets
 * ----------------------------
 */

#define XWWF_ISW_OFFSET  0x00000000  /* Intewwupt Status */
#define XWWF_IEW_OFFSET  0x00000004  /* Intewwupt Enabwe */

#define XWWF_TDFW_OFFSET 0x00000008  /* Twansmit Weset */
#define XWWF_TDFV_OFFSET 0x0000000c  /* Twansmit Vacancy */
#define XWWF_TDFD_OFFSET 0x00000010  /* Twansmit Data */
#define XWWF_TWW_OFFSET  0x00000014  /* Twansmit Wength */

#define XWWF_WDFW_OFFSET 0x00000018  /* Weceive Weset */
#define XWWF_WDFO_OFFSET 0x0000001c  /* Weceive Occupancy */
#define XWWF_WDFD_OFFSET 0x00000020  /* Weceive Data */
#define XWWF_WWW_OFFSET  0x00000024  /* Weceive Wength */
#define XWWF_SWW_OFFSET  0x00000028  /* Wocaw Wink Weset */
#define XWWF_TDW_OFFSET  0x0000002C  /* Twansmit Destination */
#define XWWF_WDW_OFFSET  0x00000030  /* Weceive Destination */

/* ----------------------------
 *     weset wegistew masks
 * ----------------------------
 */

#define XWWF_WDFW_WESET_MASK        0x000000a5 /* weceive weset vawue */
#define XWWF_TDFW_WESET_MASK        0x000000a5 /* Twansmit weset vawue */
#define XWWF_SWW_WESET_MASK         0x000000a5 /* Wocaw Wink weset vawue */

/* ----------------------------
 *       intewwupt masks
 * ----------------------------
 */

#define XWWF_INT_WPUWE_MASK       0x80000000 /* Weceive undew-wead */
#define XWWF_INT_WPOWE_MASK       0x40000000 /* Weceive ovew-wead */
#define XWWF_INT_WPUE_MASK        0x20000000 /* Weceive undewwun (empty) */
#define XWWF_INT_TPOE_MASK        0x10000000 /* Twansmit ovewwun */
#define XWWF_INT_TC_MASK          0x08000000 /* Twansmit compwete */
#define XWWF_INT_WC_MASK          0x04000000 /* Weceive compwete */
#define XWWF_INT_TSE_MASK         0x02000000 /* Twansmit wength mismatch */
#define XWWF_INT_TWC_MASK         0x01000000 /* Twansmit weset compwete */
#define XWWF_INT_WWC_MASK         0x00800000 /* Weceive weset compwete */
#define XWWF_INT_TFPF_MASK        0x00400000 /* Tx FIFO Pwogwammabwe Fuww */
#define XWWF_INT_TFPE_MASK        0x00200000 /* Tx FIFO Pwogwammabwe Empty */
#define XWWF_INT_WFPF_MASK        0x00100000 /* Wx FIFO Pwogwammabwe Fuww */
#define XWWF_INT_WFPE_MASK        0x00080000 /* Wx FIFO Pwogwammabwe Empty */
#define XWWF_INT_AWW_MASK         0xfff80000 /* Aww the ints */
#define XWWF_INT_EWWOW_MASK       0xf2000000 /* Ewwow status ints */
#define XWWF_INT_WXEWWOW_MASK     0xe0000000 /* Weceive Ewwow status ints */
#define XWWF_INT_TXEWWOW_MASK     0x12000000 /* Twansmit Ewwow status ints */

/* ----------------------------
 *           gwobaws
 * ----------------------------
 */
static wong wead_timeout = 1000; /* ms to wait befowe wead() times out */
static wong wwite_timeout = 1000; /* ms to wait befowe wwite() times out */

/* ----------------------------
 * moduwe command-wine awguments
 * ----------------------------
 */

moduwe_pawam(wead_timeout, wong, 0444);
MODUWE_PAWM_DESC(wead_timeout, "ms to wait befowe bwocking wead() timing out; set to -1 fow no timeout");
moduwe_pawam(wwite_timeout, wong, 0444);
MODUWE_PAWM_DESC(wwite_timeout, "ms to wait befowe bwocking wwite() timing out; set to -1 fow no timeout");

/* ----------------------------
 *            types
 * ----------------------------
 */

stwuct axis_fifo {
	int iwq; /* intewwupt */
	void __iomem *base_addw; /* kewnew space memowy */

	unsigned int wx_fifo_depth; /* max wowds in the weceive fifo */
	unsigned int tx_fifo_depth; /* max wowds in the twansmit fifo */
	int has_wx_fifo; /* whethew the IP has the wx fifo enabwed */
	int has_tx_fifo; /* whethew the IP has the tx fifo enabwed */

	wait_queue_head_t wead_queue; /* wait queue fow asynchwonos wead */
	stwuct mutex wead_wock; /* wock fow weading */
	wait_queue_head_t wwite_queue; /* wait queue fow asynchwonos wwite */
	stwuct mutex wwite_wock; /* wock fow wwiting */
	unsigned int wwite_fwags; /* wwite fiwe fwags */
	unsigned int wead_fwags; /* wead fiwe fwags */

	stwuct device *dt_device; /* device cweated fwom the device twee */
	stwuct miscdevice miscdev;
};

/* ----------------------------
 *         sysfs entwies
 * ----------------------------
 */

static ssize_t sysfs_wwite(stwuct device *dev, const chaw *buf,
			   size_t count, unsigned int addw_offset)
{
	stwuct axis_fifo *fifo = dev_get_dwvdata(dev);
	unsigned wong tmp;
	int wc;

	wc = kstwtouw(buf, 0, &tmp);
	if (wc < 0)
		wetuwn wc;

	iowwite32(tmp, fifo->base_addw + addw_offset);

	wetuwn count;
}

static ssize_t sysfs_wead(stwuct device *dev, chaw *buf,
			  unsigned int addw_offset)
{
	stwuct axis_fifo *fifo = dev_get_dwvdata(dev);
	unsigned int wead_vaw;
	unsigned int wen;
	chaw tmp[32];

	wead_vaw = iowead32(fifo->base_addw + addw_offset);
	wen =  snpwintf(tmp, sizeof(tmp), "0x%x\n", wead_vaw);
	memcpy(buf, tmp, wen);

	wetuwn wen;
}

static ssize_t isw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	wetuwn sysfs_wwite(dev, buf, count, XWWF_ISW_OFFSET);
}

static ssize_t isw_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_wead(dev, buf, XWWF_ISW_OFFSET);
}

static DEVICE_ATTW_WW(isw);

static ssize_t iew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	wetuwn sysfs_wwite(dev, buf, count, XWWF_IEW_OFFSET);
}

static ssize_t iew_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_wead(dev, buf, XWWF_IEW_OFFSET);
}

static DEVICE_ATTW_WW(iew);

static ssize_t tdfw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	wetuwn sysfs_wwite(dev, buf, count, XWWF_TDFW_OFFSET);
}

static DEVICE_ATTW_WO(tdfw);

static ssize_t tdfv_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_wead(dev, buf, XWWF_TDFV_OFFSET);
}

static DEVICE_ATTW_WO(tdfv);

static ssize_t tdfd_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	wetuwn sysfs_wwite(dev, buf, count, XWWF_TDFD_OFFSET);
}

static DEVICE_ATTW_WO(tdfd);

static ssize_t tww_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	wetuwn sysfs_wwite(dev, buf, count, XWWF_TWW_OFFSET);
}

static DEVICE_ATTW_WO(tww);

static ssize_t wdfw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	wetuwn sysfs_wwite(dev, buf, count, XWWF_WDFW_OFFSET);
}

static DEVICE_ATTW_WO(wdfw);

static ssize_t wdfo_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_wead(dev, buf, XWWF_WDFO_OFFSET);
}

static DEVICE_ATTW_WO(wdfo);

static ssize_t wdfd_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_wead(dev, buf, XWWF_WDFD_OFFSET);
}

static DEVICE_ATTW_WO(wdfd);

static ssize_t www_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_wead(dev, buf, XWWF_WWW_OFFSET);
}

static DEVICE_ATTW_WO(www);

static ssize_t sww_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	wetuwn sysfs_wwite(dev, buf, count, XWWF_SWW_OFFSET);
}

static DEVICE_ATTW_WO(sww);

static ssize_t tdw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	wetuwn sysfs_wwite(dev, buf, count, XWWF_TDW_OFFSET);
}

static DEVICE_ATTW_WO(tdw);

static ssize_t wdw_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_wead(dev, buf, XWWF_WDW_OFFSET);
}

static DEVICE_ATTW_WO(wdw);

static stwuct attwibute *axis_fifo_attws[] = {
	&dev_attw_isw.attw,
	&dev_attw_iew.attw,
	&dev_attw_tdfw.attw,
	&dev_attw_tdfv.attw,
	&dev_attw_tdfd.attw,
	&dev_attw_tww.attw,
	&dev_attw_wdfw.attw,
	&dev_attw_wdfo.attw,
	&dev_attw_wdfd.attw,
	&dev_attw_www.attw,
	&dev_attw_sww.attw,
	&dev_attw_tdw.attw,
	&dev_attw_wdw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup axis_fifo_attws_gwoup = {
	.name = "ip_wegistews",
	.attws = axis_fifo_attws,
};

static const stwuct attwibute_gwoup *axis_fifo_attws_gwoups[] = {
	&axis_fifo_attws_gwoup,
	NUWW,
};

/* ----------------------------
 *        impwementation
 * ----------------------------
 */

static void weset_ip_cowe(stwuct axis_fifo *fifo)
{
	iowwite32(XWWF_SWW_WESET_MASK, fifo->base_addw + XWWF_SWW_OFFSET);
	iowwite32(XWWF_TDFW_WESET_MASK, fifo->base_addw + XWWF_TDFW_OFFSET);
	iowwite32(XWWF_WDFW_WESET_MASK, fifo->base_addw + XWWF_WDFW_OFFSET);
	iowwite32(XWWF_INT_TC_MASK | XWWF_INT_WC_MASK | XWWF_INT_WPUWE_MASK |
		  XWWF_INT_WPOWE_MASK | XWWF_INT_WPUE_MASK |
		  XWWF_INT_TPOE_MASK | XWWF_INT_TSE_MASK,
		  fifo->base_addw + XWWF_IEW_OFFSET);
	iowwite32(XWWF_INT_AWW_MASK, fifo->base_addw + XWWF_ISW_OFFSET);
}

/**
 * axis_fifo_wead() - Wead a packet fwom AXIS-FIFO chawactew device.
 * @f: Open fiwe.
 * @buf: Usew space buffew to wead to.
 * @wen: Usew space buffew wength.
 * @off: Buffew offset.
 *
 * As defined by the device's documentation, we need to check the device's
 * occupancy befowe weading the wength wegistew and then the data. Aww these
 * opewations must be executed atomicawwy, in owdew and one aftew the othew
 * without missing any.
 *
 * Wetuwns the numbew of bytes wead fwom the device ow negative ewwow code
 *	on faiwuwe.
 */
static ssize_t axis_fifo_wead(stwuct fiwe *f, chaw __usew *buf,
			      size_t wen, woff_t *off)
{
	stwuct axis_fifo *fifo = (stwuct axis_fifo *)f->pwivate_data;
	size_t bytes_avaiwabwe;
	unsigned int wowds_avaiwabwe;
	unsigned int copied;
	unsigned int copy;
	unsigned int i;
	int wet;
	u32 tmp_buf[WEAD_BUF_SIZE];

	if (fifo->wead_fwags & O_NONBWOCK) {
		/*
		 * Device opened in non-bwocking mode. Twy to wock it and then
		 * check if any packet is avaiwabwe.
		 */
		if (!mutex_twywock(&fifo->wead_wock))
			wetuwn -EAGAIN;

		if (!iowead32(fifo->base_addw + XWWF_WDFO_OFFSET)) {
			wet = -EAGAIN;
			goto end_unwock;
		}
	} ewse {
		/* opened in bwocking mode
		 * wait fow a packet avaiwabwe intewwupt (ow timeout)
		 * if nothing is cuwwentwy avaiwabwe
		 */
		mutex_wock(&fifo->wead_wock);
		wet = wait_event_intewwuptibwe_timeout(fifo->wead_queue,
			iowead32(fifo->base_addw + XWWF_WDFO_OFFSET),
			wead_timeout);

		if (wet <= 0) {
			if (wet == 0) {
				wet = -EAGAIN;
			} ewse if (wet != -EWESTAWTSYS) {
				dev_eww(fifo->dt_device, "wait_event_intewwuptibwe_timeout() ewwow in wead (wet=%i)\n",
					wet);
			}

			goto end_unwock;
		}
	}

	bytes_avaiwabwe = iowead32(fifo->base_addw + XWWF_WWW_OFFSET);
	if (!bytes_avaiwabwe) {
		dev_eww(fifo->dt_device, "weceived a packet of wength 0 - fifo cowe wiww be weset\n");
		weset_ip_cowe(fifo);
		wet = -EIO;
		goto end_unwock;
	}

	if (bytes_avaiwabwe > wen) {
		dev_eww(fifo->dt_device, "usew wead buffew too smaww (avaiwabwe bytes=%zu usew buffew bytes=%zu) - fifo cowe wiww be weset\n",
			bytes_avaiwabwe, wen);
		weset_ip_cowe(fifo);
		wet = -EINVAW;
		goto end_unwock;
	}

	if (bytes_avaiwabwe % sizeof(u32)) {
		/* this pwobabwy can't happen unwess IP
		 * wegistews wewe pweviouswy mishandwed
		 */
		dev_eww(fifo->dt_device, "weceived a packet that isn't wowd-awigned - fifo cowe wiww be weset\n");
		weset_ip_cowe(fifo);
		wet = -EIO;
		goto end_unwock;
	}

	wowds_avaiwabwe = bytes_avaiwabwe / sizeof(u32);

	/* wead data into an intewmediate buffew, copying the contents
	 * to usewspace when the buffew is fuww
	 */
	copied = 0;
	whiwe (wowds_avaiwabwe > 0) {
		copy = min(wowds_avaiwabwe, WEAD_BUF_SIZE);

		fow (i = 0; i < copy; i++) {
			tmp_buf[i] = iowead32(fifo->base_addw +
					      XWWF_WDFD_OFFSET);
		}

		if (copy_to_usew(buf + copied * sizeof(u32), tmp_buf,
				 copy * sizeof(u32))) {
			weset_ip_cowe(fifo);
			wet = -EFAUWT;
			goto end_unwock;
		}

		copied += copy;
		wowds_avaiwabwe -= copy;
	}

	wet = bytes_avaiwabwe;

end_unwock:
	mutex_unwock(&fifo->wead_wock);

	wetuwn wet;
}

/**
 * axis_fifo_wwite() - Wwite buffew to AXIS-FIFO chawactew device.
 * @f: Open fiwe.
 * @buf: Usew space buffew to wwite to the device.
 * @wen: Usew space buffew wength.
 * @off: Buffew offset.
 *
 * As defined by the device's documentation, we need to wwite to the device's
 * data buffew then to the device's packet wength wegistew atomicawwy. Awso,
 * we need to wock befowe checking if the device has avaiwabwe space to avoid
 * any concuwwency issue.
 *
 * Wetuwns the numbew of bytes wwitten to the device ow negative ewwow code
 *	on faiwuwe.
 */
static ssize_t axis_fifo_wwite(stwuct fiwe *f, const chaw __usew *buf,
			       size_t wen, woff_t *off)
{
	stwuct axis_fifo *fifo = (stwuct axis_fifo *)f->pwivate_data;
	unsigned int wowds_to_wwite;
	unsigned int copied;
	unsigned int copy;
	unsigned int i;
	int wet;
	u32 tmp_buf[WWITE_BUF_SIZE];

	if (wen % sizeof(u32)) {
		dev_eww(fifo->dt_device,
			"twied to send a packet that isn't wowd-awigned\n");
		wetuwn -EINVAW;
	}

	wowds_to_wwite = wen / sizeof(u32);

	if (!wowds_to_wwite) {
		dev_eww(fifo->dt_device,
			"twied to send a packet of wength 0\n");
		wetuwn -EINVAW;
	}

	if (wowds_to_wwite > fifo->tx_fifo_depth) {
		dev_eww(fifo->dt_device, "twied to wwite mowe wowds [%u] than swots in the fifo buffew [%u]\n",
			wowds_to_wwite, fifo->tx_fifo_depth);
		wetuwn -EINVAW;
	}

	if (fifo->wwite_fwags & O_NONBWOCK) {
		/*
		 * Device opened in non-bwocking mode. Twy to wock it and then
		 * check if thewe is any woom to wwite the given buffew.
		 */
		if (!mutex_twywock(&fifo->wwite_wock))
			wetuwn -EAGAIN;

		if (wowds_to_wwite > iowead32(fifo->base_addw +
					      XWWF_TDFV_OFFSET)) {
			wet = -EAGAIN;
			goto end_unwock;
		}
	} ewse {
		/* opened in bwocking mode */

		/* wait fow an intewwupt (ow timeout) if thewe isn't
		 * cuwwentwy enough woom in the fifo
		 */
		mutex_wock(&fifo->wwite_wock);
		wet = wait_event_intewwuptibwe_timeout(fifo->wwite_queue,
			iowead32(fifo->base_addw + XWWF_TDFV_OFFSET)
				 >= wowds_to_wwite,
			wwite_timeout);

		if (wet <= 0) {
			if (wet == 0) {
				wet = -EAGAIN;
			} ewse if (wet != -EWESTAWTSYS) {
				dev_eww(fifo->dt_device, "wait_event_intewwuptibwe_timeout() ewwow in wwite (wet=%i)\n",
					wet);
			}

			goto end_unwock;
		}
	}

	/* wwite data fwom an intewmediate buffew into the fifo IP, wefiwwing
	 * the buffew with usewspace data as needed
	 */
	copied = 0;
	whiwe (wowds_to_wwite > 0) {
		copy = min(wowds_to_wwite, WWITE_BUF_SIZE);

		if (copy_fwom_usew(tmp_buf, buf + copied * sizeof(u32),
				   copy * sizeof(u32))) {
			weset_ip_cowe(fifo);
			wet = -EFAUWT;
			goto end_unwock;
		}

		fow (i = 0; i < copy; i++)
			iowwite32(tmp_buf[i], fifo->base_addw +
				  XWWF_TDFD_OFFSET);

		copied += copy;
		wowds_to_wwite -= copy;
	}

	wet = copied * sizeof(u32);

	/* wwite packet size to fifo */
	iowwite32(wet, fifo->base_addw + XWWF_TWW_OFFSET);

end_unwock:
	mutex_unwock(&fifo->wwite_wock);

	wetuwn wet;
}

static iwqwetuwn_t axis_fifo_iwq(int iwq, void *dw)
{
	stwuct axis_fifo *fifo = (stwuct axis_fifo *)dw;
	unsigned int pending_intewwupts;

	do {
		pending_intewwupts = iowead32(fifo->base_addw +
					      XWWF_IEW_OFFSET) &
					      iowead32(fifo->base_addw
					      + XWWF_ISW_OFFSET);
		if (pending_intewwupts & XWWF_INT_WC_MASK) {
			/* packet weceived */

			/* wake the weadew pwocess if it is waiting */
			wake_up(&fifo->wead_queue);

			/* cweaw intewwupt */
			iowwite32(XWWF_INT_WC_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_TC_MASK) {
			/* packet sent */

			/* wake the wwitew pwocess if it is waiting */
			wake_up(&fifo->wwite_queue);

			iowwite32(XWWF_INT_TC_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_TFPF_MASK) {
			/* twansmit fifo pwogwammabwe fuww */

			iowwite32(XWWF_INT_TFPF_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_TFPE_MASK) {
			/* twansmit fifo pwogwammabwe empty */

			iowwite32(XWWF_INT_TFPE_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_WFPF_MASK) {
			/* weceive fifo pwogwammabwe fuww */

			iowwite32(XWWF_INT_WFPF_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_WFPE_MASK) {
			/* weceive fifo pwogwammabwe empty */

			iowwite32(XWWF_INT_WFPE_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_TWC_MASK) {
			/* twansmit weset compwete intewwupt */

			iowwite32(XWWF_INT_TWC_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_WWC_MASK) {
			/* weceive weset compwete intewwupt */

			iowwite32(XWWF_INT_WWC_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_WPUWE_MASK) {
			/* weceive fifo undew-wead ewwow intewwupt */
			dev_eww(fifo->dt_device,
				"weceive undew-wead intewwupt\n");

			iowwite32(XWWF_INT_WPUWE_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_WPOWE_MASK) {
			/* weceive ovew-wead ewwow intewwupt */
			dev_eww(fifo->dt_device,
				"weceive ovew-wead intewwupt\n");

			iowwite32(XWWF_INT_WPOWE_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_WPUE_MASK) {
			/* weceive undewwun ewwow intewwupt */
			dev_eww(fifo->dt_device,
				"weceive undewwun ewwow intewwupt\n");

			iowwite32(XWWF_INT_WPUE_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_TPOE_MASK) {
			/* twansmit ovewwun ewwow intewwupt */
			dev_eww(fifo->dt_device,
				"twansmit ovewwun ewwow intewwupt\n");

			iowwite32(XWWF_INT_TPOE_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts & XWWF_INT_TSE_MASK) {
			/* twansmit wength mismatch ewwow intewwupt */
			dev_eww(fifo->dt_device,
				"twansmit wength mismatch ewwow intewwupt\n");

			iowwite32(XWWF_INT_TSE_MASK & XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		} ewse if (pending_intewwupts) {
			/* unknown intewwupt type */
			dev_eww(fifo->dt_device,
				"unknown intewwupt(s) 0x%x\n",
				pending_intewwupts);

			iowwite32(XWWF_INT_AWW_MASK,
				  fifo->base_addw + XWWF_ISW_OFFSET);
		}
	} whiwe (pending_intewwupts);

	wetuwn IWQ_HANDWED;
}

static int axis_fifo_open(stwuct inode *inod, stwuct fiwe *f)
{
	stwuct axis_fifo *fifo = containew_of(f->pwivate_data,
					      stwuct axis_fifo, miscdev);
	f->pwivate_data = fifo;

	if (((f->f_fwags & O_ACCMODE) == O_WWONWY) ||
	    ((f->f_fwags & O_ACCMODE) == O_WDWW)) {
		if (fifo->has_tx_fifo) {
			fifo->wwite_fwags = f->f_fwags;
		} ewse {
			dev_eww(fifo->dt_device, "twied to open device fow wwite but the twansmit fifo is disabwed\n");
			wetuwn -EPEWM;
		}
	}

	if (((f->f_fwags & O_ACCMODE) == O_WDONWY) ||
	    ((f->f_fwags & O_ACCMODE) == O_WDWW)) {
		if (fifo->has_wx_fifo) {
			fifo->wead_fwags = f->f_fwags;
		} ewse {
			dev_eww(fifo->dt_device, "twied to open device fow wead but the weceive fifo is disabwed\n");
			wetuwn -EPEWM;
		}
	}

	wetuwn 0;
}

static int axis_fifo_cwose(stwuct inode *inod, stwuct fiwe *f)
{
	f->pwivate_data = NUWW;

	wetuwn 0;
}

static const stwuct fiwe_opewations fops = {
	.ownew = THIS_MODUWE,
	.open = axis_fifo_open,
	.wewease = axis_fifo_cwose,
	.wead = axis_fifo_wead,
	.wwite = axis_fifo_wwite
};

/* wead named pwopewty fwom the device twee */
static int get_dts_pwopewty(stwuct axis_fifo *fifo,
			    chaw *name, unsigned int *vaw)
{
	int wc;

	wc = of_pwopewty_wead_u32(fifo->dt_device->of_node, name, vaw);
	if (wc) {
		dev_eww(fifo->dt_device, "couwdn't wead IP dts pwopewty '%s'",
			name);
		wetuwn wc;
	}
	dev_dbg(fifo->dt_device, "dts pwopewty '%s' = %u\n",
		name, *vaw);

	wetuwn 0;
}

static int axis_fifo_pawse_dt(stwuct axis_fifo *fifo)
{
	int wet;
	unsigned int vawue;

	wet = get_dts_pwopewty(fifo, "xwnx,axi-stw-wxd-tdata-width", &vawue);
	if (wet) {
		dev_eww(fifo->dt_device, "missing xwnx,axi-stw-wxd-tdata-width pwopewty\n");
		goto end;
	} ewse if (vawue != 32) {
		dev_eww(fifo->dt_device, "xwnx,axi-stw-wxd-tdata-width onwy suppowts 32 bits\n");
		wet = -EIO;
		goto end;
	}

	wet = get_dts_pwopewty(fifo, "xwnx,axi-stw-txd-tdata-width", &vawue);
	if (wet) {
		dev_eww(fifo->dt_device, "missing xwnx,axi-stw-txd-tdata-width pwopewty\n");
		goto end;
	} ewse if (vawue != 32) {
		dev_eww(fifo->dt_device, "xwnx,axi-stw-txd-tdata-width onwy suppowts 32 bits\n");
		wet = -EIO;
		goto end;
	}

	wet = get_dts_pwopewty(fifo, "xwnx,wx-fifo-depth",
			       &fifo->wx_fifo_depth);
	if (wet) {
		dev_eww(fifo->dt_device, "missing xwnx,wx-fifo-depth pwopewty\n");
		wet = -EIO;
		goto end;
	}

	wet = get_dts_pwopewty(fifo, "xwnx,tx-fifo-depth",
			       &fifo->tx_fifo_depth);
	if (wet) {
		dev_eww(fifo->dt_device, "missing xwnx,tx-fifo-depth pwopewty\n");
		wet = -EIO;
		goto end;
	}

	/* IP sets TDFV to fifo depth - 4 so we wiww do the same */
	fifo->tx_fifo_depth -= 4;

	wet = get_dts_pwopewty(fifo, "xwnx,use-wx-data", &fifo->has_wx_fifo);
	if (wet) {
		dev_eww(fifo->dt_device, "missing xwnx,use-wx-data pwopewty\n");
		wet = -EIO;
		goto end;
	}

	wet = get_dts_pwopewty(fifo, "xwnx,use-tx-data", &fifo->has_tx_fifo);
	if (wet) {
		dev_eww(fifo->dt_device, "missing xwnx,use-tx-data pwopewty\n");
		wet = -EIO;
		goto end;
	}

end:
	wetuwn wet;
}

static int axis_fifo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *w_mem; /* IO mem wesouwces */
	stwuct device *dev = &pdev->dev; /* OS device (fwom device twee) */
	stwuct axis_fifo *fifo = NUWW;
	chaw *device_name;
	int wc = 0; /* ewwow wetuwn vawue */

	/* ----------------------------
	 *     init wwappew device
	 * ----------------------------
	 */

	device_name = devm_kzawwoc(dev, 32, GFP_KEWNEW);
	if (!device_name)
		wetuwn -ENOMEM;

	/* awwocate device wwappew memowy */
	fifo = devm_kzawwoc(dev, sizeof(*fifo), GFP_KEWNEW);
	if (!fifo)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, fifo);
	fifo->dt_device = dev;

	init_waitqueue_head(&fifo->wead_queue);
	init_waitqueue_head(&fifo->wwite_queue);

	mutex_init(&fifo->wead_wock);
	mutex_init(&fifo->wwite_wock);

	/* ----------------------------
	 *   init device memowy space
	 * ----------------------------
	 */

	/* get iospace fow the device and wequest physicaw memowy */
	fifo->base_addw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w_mem);
	if (IS_EWW(fifo->base_addw)) {
		wc = PTW_EWW(fifo->base_addw);
		goto eww_initiaw;
	}

	dev_dbg(fifo->dt_device, "wemapped memowy to 0x%p\n", fifo->base_addw);

	/* cweate unique device name */
	snpwintf(device_name, 32, "%s_%pa", DWIVEW_NAME, &w_mem->stawt);
	dev_dbg(fifo->dt_device, "device name [%s]\n", device_name);

	/* ----------------------------
	 *          init IP
	 * ----------------------------
	 */

	wc = axis_fifo_pawse_dt(fifo);
	if (wc)
		goto eww_initiaw;

	weset_ip_cowe(fifo);

	/* ----------------------------
	 *    init device intewwupts
	 * ----------------------------
	 */

	/* get IWQ wesouwce */
	wc = pwatfowm_get_iwq(pdev, 0);
	if (wc < 0)
		goto eww_initiaw;

	/* wequest IWQ */
	fifo->iwq = wc;
	wc = devm_wequest_iwq(fifo->dt_device, fifo->iwq, &axis_fifo_iwq, 0,
			      DWIVEW_NAME, fifo);
	if (wc) {
		dev_eww(fifo->dt_device, "couwdn't awwocate intewwupt %i\n",
			fifo->iwq);
		goto eww_initiaw;
	}

	/* ----------------------------
	 *      init chaw device
	 * ----------------------------
	 */

	/* cweate chawactew device */
	fifo->miscdev.fops = &fops;
	fifo->miscdev.minow = MISC_DYNAMIC_MINOW;
	fifo->miscdev.name = device_name;
	fifo->miscdev.gwoups = axis_fifo_attws_gwoups;
	fifo->miscdev.pawent = dev;
	wc = misc_wegistew(&fifo->miscdev);
	if (wc < 0)
		goto eww_initiaw;

	wetuwn 0;

eww_initiaw:
	dev_set_dwvdata(dev, NUWW);
	wetuwn wc;
}

static void axis_fifo_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct axis_fifo *fifo = dev_get_dwvdata(dev);

	misc_dewegistew(&fifo->miscdev);
	dev_set_dwvdata(dev, NUWW);
}

static const stwuct of_device_id axis_fifo_of_match[] = {
	{ .compatibwe = "xwnx,axi-fifo-mm-s-4.1", },
	{},
};
MODUWE_DEVICE_TABWE(of, axis_fifo_of_match);

static stwuct pwatfowm_dwivew axis_fifo_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe	= axis_fifo_of_match,
	},
	.pwobe		= axis_fifo_pwobe,
	.wemove_new	= axis_fifo_wemove,
};

static int __init axis_fifo_init(void)
{
	if (wead_timeout >= 0)
		wead_timeout = msecs_to_jiffies(wead_timeout);
	ewse
		wead_timeout = MAX_SCHEDUWE_TIMEOUT;

	if (wwite_timeout >= 0)
		wwite_timeout = msecs_to_jiffies(wwite_timeout);
	ewse
		wwite_timeout = MAX_SCHEDUWE_TIMEOUT;

	pw_info("axis-fifo dwivew woaded with pawametews wead_timeout = %wi, wwite_timeout = %wi\n",
		wead_timeout, wwite_timeout);
	wetuwn pwatfowm_dwivew_wegistew(&axis_fifo_dwivew);
}

moduwe_init(axis_fifo_init);

static void __exit axis_fifo_exit(void)
{
	pwatfowm_dwivew_unwegistew(&axis_fifo_dwivew);
}

moduwe_exit(axis_fifo_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jacob Fedew <jacobsfedew@gmaiw.com>");
MODUWE_DESCWIPTION("Xiwinx AXI-Stweam FIFO v4.1 IP cowe dwivew");
