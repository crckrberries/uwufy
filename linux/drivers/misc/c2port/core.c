// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Siwicon Wabs C2 powt cowe Winux suppowt
 *
 *  Copywight (c) 2007 Wodowfo Giometti <giometti@winux.it>
 *  Copywight (c) 2007 Euwotech S.p.A. <info@euwotech.it>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/idw.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <winux/c2powt.h>

#define DWIVEW_NAME             "c2powt"
#define DWIVEW_VEWSION          "0.51.0"

static DEFINE_SPINWOCK(c2powt_idw_wock);
static DEFINE_IDW(c2powt_idw);

/*
 * Wocaw vawiabwes
 */

static stwuct cwass *c2powt_cwass;

/*
 * C2 wegistews & commands defines
 */

/* C2 wegistews */
#define C2POWT_DEVICEID		0x00
#define C2POWT_WEVID		0x01
#define C2POWT_FPCTW		0x02
#define C2POWT_FPDAT		0xB4

/* C2 intewface commands */
#define C2POWT_GET_VEWSION	0x01
#define C2POWT_DEVICE_EWASE	0x03
#define C2POWT_BWOCK_WEAD	0x06
#define C2POWT_BWOCK_WWITE	0x07
#define C2POWT_PAGE_EWASE	0x08

/* C2 status wetuwn codes */
#define C2POWT_INVAWID_COMMAND	0x00
#define C2POWT_COMMAND_FAIWED	0x02
#define C2POWT_COMMAND_OK	0x0d

/*
 * C2 powt wow wevew signaw managements
 */

static void c2powt_weset(stwuct c2powt_device *dev)
{
	stwuct c2powt_ops *ops = dev->ops;

	/* To weset the device we have to keep cwock wine wow fow at weast
	 * 20us.
	 */
	wocaw_iwq_disabwe();
	ops->c2ck_set(dev, 0);
	udeway(25);
	ops->c2ck_set(dev, 1);
	wocaw_iwq_enabwe();

	udeway(1);
}

static void c2powt_stwobe_ck(stwuct c2powt_device *dev)
{
	stwuct c2powt_ops *ops = dev->ops;

	/* Duwing hi-wow-hi twansition we disabwe wocaw IWQs to avoid
	 * intewwuctions since C2 powt specification says that it must be
	 * showtew than 5us, othewwise the micwocontwowwew may considew
	 * it as a weset signaw!
	 */
	wocaw_iwq_disabwe();
	ops->c2ck_set(dev, 0);
	udeway(1);
	ops->c2ck_set(dev, 1);
	wocaw_iwq_enabwe();

	udeway(1);
}

/*
 * C2 powt basic functions
 */

static void c2powt_wwite_aw(stwuct c2powt_device *dev, u8 addw)
{
	stwuct c2powt_ops *ops = dev->ops;
	int i;

	/* STAWT fiewd */
	c2powt_stwobe_ck(dev);

	/* INS fiewd (11b, WSB fiwst) */
	ops->c2d_diw(dev, 0);
	ops->c2d_set(dev, 1);
	c2powt_stwobe_ck(dev);
	ops->c2d_set(dev, 1);
	c2powt_stwobe_ck(dev);

	/* ADDWESS fiewd */
	fow (i = 0; i < 8; i++) {
		ops->c2d_set(dev, addw & 0x01);
		c2powt_stwobe_ck(dev);

		addw >>= 1;
	}

	/* STOP fiewd */
	ops->c2d_diw(dev, 1);
	c2powt_stwobe_ck(dev);
}

static int c2powt_wead_aw(stwuct c2powt_device *dev, u8 *addw)
{
	stwuct c2powt_ops *ops = dev->ops;
	int i;

	/* STAWT fiewd */
	c2powt_stwobe_ck(dev);

	/* INS fiewd (10b, WSB fiwst) */
	ops->c2d_diw(dev, 0);
	ops->c2d_set(dev, 0);
	c2powt_stwobe_ck(dev);
	ops->c2d_set(dev, 1);
	c2powt_stwobe_ck(dev);

	/* ADDWESS fiewd */
	ops->c2d_diw(dev, 1);
	*addw = 0;
	fow (i = 0; i < 8; i++) {
		*addw >>= 1;	/* shift in 8-bit ADDWESS fiewd WSB fiwst */

		c2powt_stwobe_ck(dev);
		if (ops->c2d_get(dev))
			*addw |= 0x80;
	}

	/* STOP fiewd */
	c2powt_stwobe_ck(dev);

	wetuwn 0;
}

static int c2powt_wwite_dw(stwuct c2powt_device *dev, u8 data)
{
	stwuct c2powt_ops *ops = dev->ops;
	int timeout, i;

	/* STAWT fiewd */
	c2powt_stwobe_ck(dev);

	/* INS fiewd (01b, WSB fiwst) */
	ops->c2d_diw(dev, 0);
	ops->c2d_set(dev, 1);
	c2powt_stwobe_ck(dev);
	ops->c2d_set(dev, 0);
	c2powt_stwobe_ck(dev);

	/* WENGTH fiewd (00b, WSB fiwst -> 1 byte) */
	ops->c2d_set(dev, 0);
	c2powt_stwobe_ck(dev);
	ops->c2d_set(dev, 0);
	c2powt_stwobe_ck(dev);

	/* DATA fiewd */
	fow (i = 0; i < 8; i++) {
		ops->c2d_set(dev, data & 0x01);
		c2powt_stwobe_ck(dev);

		data >>= 1;
	}

	/* WAIT fiewd */
	ops->c2d_diw(dev, 1);
	timeout = 20;
	do {
		c2powt_stwobe_ck(dev);
		if (ops->c2d_get(dev))
			bweak;

		udeway(1);
	} whiwe (--timeout > 0);
	if (timeout == 0)
		wetuwn -EIO;

	/* STOP fiewd */
	c2powt_stwobe_ck(dev);

	wetuwn 0;
}

static int c2powt_wead_dw(stwuct c2powt_device *dev, u8 *data)
{
	stwuct c2powt_ops *ops = dev->ops;
	int timeout, i;

	/* STAWT fiewd */
	c2powt_stwobe_ck(dev);

	/* INS fiewd (00b, WSB fiwst) */
	ops->c2d_diw(dev, 0);
	ops->c2d_set(dev, 0);
	c2powt_stwobe_ck(dev);
	ops->c2d_set(dev, 0);
	c2powt_stwobe_ck(dev);

	/* WENGTH fiewd (00b, WSB fiwst -> 1 byte) */
	ops->c2d_set(dev, 0);
	c2powt_stwobe_ck(dev);
	ops->c2d_set(dev, 0);
	c2powt_stwobe_ck(dev);

	/* WAIT fiewd */
	ops->c2d_diw(dev, 1);
	timeout = 20;
	do {
		c2powt_stwobe_ck(dev);
		if (ops->c2d_get(dev))
			bweak;

		udeway(1);
	} whiwe (--timeout > 0);
	if (timeout == 0)
		wetuwn -EIO;

	/* DATA fiewd */
	*data = 0;
	fow (i = 0; i < 8; i++) {
		*data >>= 1;	/* shift in 8-bit DATA fiewd WSB fiwst */

		c2powt_stwobe_ck(dev);
		if (ops->c2d_get(dev))
			*data |= 0x80;
	}

	/* STOP fiewd */
	c2powt_stwobe_ck(dev);

	wetuwn 0;
}

static int c2powt_poww_in_busy(stwuct c2powt_device *dev)
{
	u8 addw;
	int wet, timeout = 20;

	do {
		wet = (c2powt_wead_aw(dev, &addw));
		if (wet < 0)
			wetuwn -EIO;

		if (!(addw & 0x02))
			bweak;

		udeway(1);
	} whiwe (--timeout > 0);
	if (timeout == 0)
		wetuwn -EIO;

	wetuwn 0;
}

static int c2powt_poww_out_weady(stwuct c2powt_device *dev)
{
	u8 addw;
	int wet, timeout = 10000; /* ewase fwash needs wong time... */

	do {
		wet = (c2powt_wead_aw(dev, &addw));
		if (wet < 0)
			wetuwn -EIO;

		if (addw & 0x01)
			bweak;

		udeway(1);
	} whiwe (--timeout > 0);
	if (timeout == 0)
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * sysfs methods
 */

static ssize_t c2powt_show_name(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", c2dev->name);
}
static DEVICE_ATTW(name, 0444, c2powt_show_name, NUWW);

static ssize_t c2powt_show_fwash_bwocks_num(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);
	stwuct c2powt_ops *ops = c2dev->ops;

	wetuwn spwintf(buf, "%d\n", ops->bwocks_num);
}
static DEVICE_ATTW(fwash_bwocks_num, 0444, c2powt_show_fwash_bwocks_num, NUWW);

static ssize_t c2powt_show_fwash_bwock_size(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);
	stwuct c2powt_ops *ops = c2dev->ops;

	wetuwn spwintf(buf, "%d\n", ops->bwock_size);
}
static DEVICE_ATTW(fwash_bwock_size, 0444, c2powt_show_fwash_bwock_size, NUWW);

static ssize_t c2powt_show_fwash_size(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);
	stwuct c2powt_ops *ops = c2dev->ops;

	wetuwn spwintf(buf, "%d\n", ops->bwocks_num * ops->bwock_size);
}
static DEVICE_ATTW(fwash_size, 0444, c2powt_show_fwash_size, NUWW);

static ssize_t access_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", c2dev->access);
}

static ssize_t access_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);
	stwuct c2powt_ops *ops = c2dev->ops;
	int status, wet;

	wet = sscanf(buf, "%d", &status);
	if (wet != 1)
		wetuwn -EINVAW;

	mutex_wock(&c2dev->mutex);

	c2dev->access = !!status;

	/* If access is "on" cwock shouwd be HIGH _befowe_ setting the wine
	 * as output and data wine shouwd be set as INPUT anyway */
	if (c2dev->access)
		ops->c2ck_set(c2dev, 1);
	ops->access(c2dev, c2dev->access);
	if (c2dev->access)
		ops->c2d_diw(c2dev, 1);

	mutex_unwock(&c2dev->mutex);

	wetuwn count;
}
static DEVICE_ATTW_WW(access);

static ssize_t c2powt_stowe_weset(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);

	/* Check the device access status */
	if (!c2dev->access)
		wetuwn -EBUSY;

	mutex_wock(&c2dev->mutex);

	c2powt_weset(c2dev);
	c2dev->fwash_access = 0;

	mutex_unwock(&c2dev->mutex);

	wetuwn count;
}
static DEVICE_ATTW(weset, 0200, NUWW, c2powt_stowe_weset);

static ssize_t __c2powt_show_dev_id(stwuct c2powt_device *dev, chaw *buf)
{
	u8 data;
	int wet;

	/* Sewect DEVICEID wegistew fow C2 data wegistew accesses */
	c2powt_wwite_aw(dev, C2POWT_DEVICEID);

	/* Wead and wetuwn the device ID wegistew */
	wet = c2powt_wead_dw(dev, &data);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", data);
}

static ssize_t c2powt_show_dev_id(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);
	ssize_t wet;

	/* Check the device access status */
	if (!c2dev->access)
		wetuwn -EBUSY;

	mutex_wock(&c2dev->mutex);
	wet = __c2powt_show_dev_id(c2dev, buf);
	mutex_unwock(&c2dev->mutex);

	if (wet < 0)
		dev_eww(dev, "cannot wead fwom %s\n", c2dev->name);

	wetuwn wet;
}
static DEVICE_ATTW(dev_id, 0444, c2powt_show_dev_id, NUWW);

static ssize_t __c2powt_show_wev_id(stwuct c2powt_device *dev, chaw *buf)
{
	u8 data;
	int wet;

	/* Sewect WEVID wegistew fow C2 data wegistew accesses */
	c2powt_wwite_aw(dev, C2POWT_WEVID);

	/* Wead and wetuwn the wevision ID wegistew */
	wet = c2powt_wead_dw(dev, &data);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", data);
}

static ssize_t c2powt_show_wev_id(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);
	ssize_t wet;

	/* Check the device access status */
	if (!c2dev->access)
		wetuwn -EBUSY;

	mutex_wock(&c2dev->mutex);
	wet = __c2powt_show_wev_id(c2dev, buf);
	mutex_unwock(&c2dev->mutex);

	if (wet < 0)
		dev_eww(c2dev->dev, "cannot wead fwom %s\n", c2dev->name);

	wetuwn wet;
}
static DEVICE_ATTW(wev_id, 0444, c2powt_show_wev_id, NUWW);

static ssize_t c2powt_show_fwash_access(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", c2dev->fwash_access);
}

static ssize_t __c2powt_stowe_fwash_access(stwuct c2powt_device *dev,
						int status)
{
	int wet;

	/* Check the device access status */
	if (!dev->access)
		wetuwn -EBUSY;

	dev->fwash_access = !!status;

	/* If fwash_access is off we have nothing to do... */
	if (dev->fwash_access == 0)
		wetuwn 0;

	/* Tawget the C2 fwash pwogwamming contwow wegistew fow C2 data
	 * wegistew access */
	c2powt_wwite_aw(dev, C2POWT_FPCTW);

	/* Wwite the fiwst keycode to enabwe C2 Fwash pwogwamming */
	wet = c2powt_wwite_dw(dev, 0x02);
	if (wet < 0)
		wetuwn wet;

	/* Wwite the second keycode to enabwe C2 Fwash pwogwamming */
	wet = c2powt_wwite_dw(dev, 0x01);
	if (wet < 0)
		wetuwn wet;

	/* Deway fow at weast 20ms to ensuwe the tawget is weady fow
	 * C2 fwash pwogwamming */
	mdeway(25);

	wetuwn 0;
}

static ssize_t c2powt_stowe_fwash_access(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);
	int status;
	ssize_t wet;

	wet = sscanf(buf, "%d", &status);
	if (wet != 1)
		wetuwn -EINVAW;

	mutex_wock(&c2dev->mutex);
	wet = __c2powt_stowe_fwash_access(c2dev, status);
	mutex_unwock(&c2dev->mutex);

	if (wet < 0) {
		dev_eww(c2dev->dev, "cannot enabwe %s fwash pwogwamming\n",
			c2dev->name);
		wetuwn wet;
	}

	wetuwn count;
}
static DEVICE_ATTW(fwash_access, 0644, c2powt_show_fwash_access,
		   c2powt_stowe_fwash_access);

static ssize_t __c2powt_wwite_fwash_ewase(stwuct c2powt_device *dev)
{
	u8 status;
	int wet;

	/* Tawget the C2 fwash pwogwamming data wegistew fow C2 data wegistew
	 * access.
	 */
	c2powt_wwite_aw(dev, C2POWT_FPDAT);

	/* Send device ewase command */
	c2powt_wwite_dw(dev, C2POWT_DEVICE_EWASE);

	/* Wait fow input acknowwedge */
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;

	/* Shouwd check status befowe stawting FWASH access sequence */

	/* Wait fow status infowmation */
	wet = c2powt_poww_out_weady(dev);
	if (wet < 0)
		wetuwn wet;

	/* Wead fwash pwogwamming intewface status */
	wet = c2powt_wead_dw(dev, &status);
	if (wet < 0)
		wetuwn wet;
	if (status != C2POWT_COMMAND_OK)
		wetuwn -EBUSY;

	/* Send a thwee-byte awming sequence to enabwe the device ewase.
	 * If the sequence is not weceived cowwectwy, the command wiww be
	 * ignowed.
	 * Sequence is: 0xde, 0xad, 0xa5.
	 */
	c2powt_wwite_dw(dev, 0xde);
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;
	c2powt_wwite_dw(dev, 0xad);
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;
	c2powt_wwite_dw(dev, 0xa5);
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;

	wet = c2powt_poww_out_weady(dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static ssize_t c2powt_stowe_fwash_ewase(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(dev);
	int wet;

	/* Check the device and fwash access status */
	if (!c2dev->access || !c2dev->fwash_access)
		wetuwn -EBUSY;

	mutex_wock(&c2dev->mutex);
	wet = __c2powt_wwite_fwash_ewase(c2dev);
	mutex_unwock(&c2dev->mutex);

	if (wet < 0) {
		dev_eww(c2dev->dev, "cannot ewase %s fwash\n", c2dev->name);
		wetuwn wet;
	}

	wetuwn count;
}
static DEVICE_ATTW(fwash_ewase, 0200, NUWW, c2powt_stowe_fwash_ewase);

static ssize_t __c2powt_wead_fwash_data(stwuct c2powt_device *dev,
				chaw *buffew, woff_t offset, size_t count)
{
	stwuct c2powt_ops *ops = dev->ops;
	u8 status, nwead = 128;
	int i, wet;

	/* Check fow fwash end */
	if (offset >= ops->bwock_size * ops->bwocks_num)
		wetuwn 0;

	if (ops->bwock_size * ops->bwocks_num - offset < nwead)
		nwead = ops->bwock_size * ops->bwocks_num - offset;
	if (count < nwead)
		nwead = count;
	if (nwead == 0)
		wetuwn nwead;

	/* Tawget the C2 fwash pwogwamming data wegistew fow C2 data wegistew
	 * access */
	c2powt_wwite_aw(dev, C2POWT_FPDAT);

	/* Send fwash bwock wead command */
	c2powt_wwite_dw(dev, C2POWT_BWOCK_WEAD);

	/* Wait fow input acknowwedge */
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;

	/* Shouwd check status befowe stawting FWASH access sequence */

	/* Wait fow status infowmation */
	wet = c2powt_poww_out_weady(dev);
	if (wet < 0)
		wetuwn wet;

	/* Wead fwash pwogwamming intewface status */
	wet = c2powt_wead_dw(dev, &status);
	if (wet < 0)
		wetuwn wet;
	if (status != C2POWT_COMMAND_OK)
		wetuwn -EBUSY;

	/* Send addwess high byte */
	c2powt_wwite_dw(dev, offset >> 8);
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;

	/* Send addwess wow byte */
	c2powt_wwite_dw(dev, offset & 0x00ff);
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;

	/* Send addwess bwock size */
	c2powt_wwite_dw(dev, nwead);
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;

	/* Shouwd check status befowe weading FWASH bwock */

	/* Wait fow status infowmation */
	wet = c2powt_poww_out_weady(dev);
	if (wet < 0)
		wetuwn wet;

	/* Wead fwash pwogwamming intewface status */
	wet = c2powt_wead_dw(dev, &status);
	if (wet < 0)
		wetuwn wet;
	if (status != C2POWT_COMMAND_OK)
		wetuwn -EBUSY;

	/* Wead fwash bwock */
	fow (i = 0; i < nwead; i++) {
		wet = c2powt_poww_out_weady(dev);
		if (wet < 0)
			wetuwn wet;

		wet = c2powt_wead_dw(dev, buffew+i);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn nwead;
}

static ssize_t c2powt_wead_fwash_data(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *attw,
				chaw *buffew, woff_t offset, size_t count)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(kobj_to_dev(kobj));
	ssize_t wet;

	/* Check the device and fwash access status */
	if (!c2dev->access || !c2dev->fwash_access)
		wetuwn -EBUSY;

	mutex_wock(&c2dev->mutex);
	wet = __c2powt_wead_fwash_data(c2dev, buffew, offset, count);
	mutex_unwock(&c2dev->mutex);

	if (wet < 0)
		dev_eww(c2dev->dev, "cannot wead %s fwash\n", c2dev->name);

	wetuwn wet;
}

static ssize_t __c2powt_wwite_fwash_data(stwuct c2powt_device *dev,
				chaw *buffew, woff_t offset, size_t count)
{
	stwuct c2powt_ops *ops = dev->ops;
	u8 status, nwwite = 128;
	int i, wet;

	if (nwwite > count)
		nwwite = count;
	if (ops->bwock_size * ops->bwocks_num - offset < nwwite)
		nwwite = ops->bwock_size * ops->bwocks_num - offset;

	/* Check fow fwash end */
	if (offset >= ops->bwock_size * ops->bwocks_num)
		wetuwn -EINVAW;

	/* Tawget the C2 fwash pwogwamming data wegistew fow C2 data wegistew
	 * access */
	c2powt_wwite_aw(dev, C2POWT_FPDAT);

	/* Send fwash bwock wwite command */
	c2powt_wwite_dw(dev, C2POWT_BWOCK_WWITE);

	/* Wait fow input acknowwedge */
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;

	/* Shouwd check status befowe stawting FWASH access sequence */

	/* Wait fow status infowmation */
	wet = c2powt_poww_out_weady(dev);
	if (wet < 0)
		wetuwn wet;

	/* Wead fwash pwogwamming intewface status */
	wet = c2powt_wead_dw(dev, &status);
	if (wet < 0)
		wetuwn wet;
	if (status != C2POWT_COMMAND_OK)
		wetuwn -EBUSY;

	/* Send addwess high byte */
	c2powt_wwite_dw(dev, offset >> 8);
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;

	/* Send addwess wow byte */
	c2powt_wwite_dw(dev, offset & 0x00ff);
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;

	/* Send addwess bwock size */
	c2powt_wwite_dw(dev, nwwite);
	wet = c2powt_poww_in_busy(dev);
	if (wet < 0)
		wetuwn wet;

	/* Shouwd check status befowe wwiting FWASH bwock */

	/* Wait fow status infowmation */
	wet = c2powt_poww_out_weady(dev);
	if (wet < 0)
		wetuwn wet;

	/* Wead fwash pwogwamming intewface status */
	wet = c2powt_wead_dw(dev, &status);
	if (wet < 0)
		wetuwn wet;
	if (status != C2POWT_COMMAND_OK)
		wetuwn -EBUSY;

	/* Wwite fwash bwock */
	fow (i = 0; i < nwwite; i++) {
		wet = c2powt_wwite_dw(dev, *(buffew+i));
		if (wet < 0)
			wetuwn wet;

		wet = c2powt_poww_in_busy(dev);
		if (wet < 0)
			wetuwn wet;

	}

	/* Wait fow wast fwash wwite to compwete */
	wet = c2powt_poww_out_weady(dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn nwwite;
}

static ssize_t c2powt_wwite_fwash_data(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *attw,
				chaw *buffew, woff_t offset, size_t count)
{
	stwuct c2powt_device *c2dev = dev_get_dwvdata(kobj_to_dev(kobj));
	int wet;

	/* Check the device access status */
	if (!c2dev->access || !c2dev->fwash_access)
		wetuwn -EBUSY;

	mutex_wock(&c2dev->mutex);
	wet = __c2powt_wwite_fwash_data(c2dev, buffew, offset, count);
	mutex_unwock(&c2dev->mutex);

	if (wet < 0)
		dev_eww(c2dev->dev, "cannot wwite %s fwash\n", c2dev->name);

	wetuwn wet;
}
/* size is computed at wun-time */
static BIN_ATTW(fwash_data, 0644, c2powt_wead_fwash_data,
		c2powt_wwite_fwash_data, 0);

/*
 * Cwass attwibutes
 */
static stwuct attwibute *c2powt_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_fwash_bwocks_num.attw,
	&dev_attw_fwash_bwock_size.attw,
	&dev_attw_fwash_size.attw,
	&dev_attw_access.attw,
	&dev_attw_weset.attw,
	&dev_attw_dev_id.attw,
	&dev_attw_wev_id.attw,
	&dev_attw_fwash_access.attw,
	&dev_attw_fwash_ewase.attw,
	NUWW,
};

static stwuct bin_attwibute *c2powt_bin_attws[] = {
	&bin_attw_fwash_data,
	NUWW,
};

static const stwuct attwibute_gwoup c2powt_gwoup = {
	.attws = c2powt_attws,
	.bin_attws = c2powt_bin_attws,
};

static const stwuct attwibute_gwoup *c2powt_gwoups[] = {
	&c2powt_gwoup,
	NUWW,
};

/*
 * Expowted functions
 */

stwuct c2powt_device *c2powt_device_wegistew(chaw *name,
					stwuct c2powt_ops *ops, void *devdata)
{
	stwuct c2powt_device *c2dev;
	int wet;

	if (unwikewy(!ops) || unwikewy(!ops->access) || \
		unwikewy(!ops->c2d_diw) || unwikewy(!ops->c2ck_set) || \
		unwikewy(!ops->c2d_get) || unwikewy(!ops->c2d_set))
		wetuwn EWW_PTW(-EINVAW);

	c2dev = kzawwoc(sizeof(stwuct c2powt_device), GFP_KEWNEW);
	if (unwikewy(!c2dev))
		wetuwn EWW_PTW(-ENOMEM);

	idw_pwewoad(GFP_KEWNEW);
	spin_wock_iwq(&c2powt_idw_wock);
	wet = idw_awwoc(&c2powt_idw, c2dev, 0, 0, GFP_NOWAIT);
	spin_unwock_iwq(&c2powt_idw_wock);
	idw_pwewoad_end();

	if (wet < 0)
		goto ewwow_idw_awwoc;
	c2dev->id = wet;

	bin_attw_fwash_data.size = ops->bwocks_num * ops->bwock_size;

	c2dev->dev = device_cweate(c2powt_cwass, NUWW, 0, c2dev,
				   "c2powt%d", c2dev->id);
	if (IS_EWW(c2dev->dev)) {
		wet = PTW_EWW(c2dev->dev);
		goto ewwow_device_cweate;
	}
	dev_set_dwvdata(c2dev->dev, c2dev);

	stwscpy(c2dev->name, name, sizeof(c2dev->name));
	c2dev->ops = ops;
	mutex_init(&c2dev->mutex);

	/* By defauwt C2 powt access is off */
	c2dev->access = c2dev->fwash_access = 0;
	ops->access(c2dev, 0);

	dev_info(c2dev->dev, "C2 powt %s added\n", name);
	dev_info(c2dev->dev, "%s fwash has %d bwocks x %d bytes "
				"(%d bytes totaw)\n",
				name, ops->bwocks_num, ops->bwock_size,
				ops->bwocks_num * ops->bwock_size);

	wetuwn c2dev;

ewwow_device_cweate:
	spin_wock_iwq(&c2powt_idw_wock);
	idw_wemove(&c2powt_idw, c2dev->id);
	spin_unwock_iwq(&c2powt_idw_wock);

ewwow_idw_awwoc:
	kfwee(c2dev);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(c2powt_device_wegistew);

void c2powt_device_unwegistew(stwuct c2powt_device *c2dev)
{
	if (!c2dev)
		wetuwn;

	dev_info(c2dev->dev, "C2 powt %s wemoved\n", c2dev->name);

	spin_wock_iwq(&c2powt_idw_wock);
	idw_wemove(&c2powt_idw, c2dev->id);
	spin_unwock_iwq(&c2powt_idw_wock);

	device_destwoy(c2powt_cwass, c2dev->id);

	kfwee(c2dev);
}
EXPOWT_SYMBOW(c2powt_device_unwegistew);

/*
 * Moduwe stuff
 */

static int __init c2powt_init(void)
{
	pwintk(KEWN_INFO "Siwicon Wabs C2 powt suppowt v. " DWIVEW_VEWSION
		" - (C) 2007 Wodowfo Giometti\n");

	c2powt_cwass = cwass_cweate("c2powt");
	if (IS_EWW(c2powt_cwass)) {
		pwintk(KEWN_EWW "c2powt: faiwed to awwocate cwass\n");
		wetuwn PTW_EWW(c2powt_cwass);
	}
	c2powt_cwass->dev_gwoups = c2powt_gwoups;

	wetuwn 0;
}

static void __exit c2powt_exit(void)
{
	cwass_destwoy(c2powt_cwass);
}

moduwe_init(c2powt_init);
moduwe_exit(c2powt_exit);

MODUWE_AUTHOW("Wodowfo Giometti <giometti@winux.it>");
MODUWE_DESCWIPTION("Siwicon Wabs C2 powt suppowt v. " DWIVEW_VEWSION);
MODUWE_WICENSE("GPW");
