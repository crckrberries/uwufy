// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/wandisk/gio.c - dwivew fow wandisk
 *
 * This dwivew wiww awso suppowt the I-O DATA Device, Inc. WANDISK Boawd.
 * WANDISK and USW-5P Button, WED and GIO dwivew dwive function.
 *
 *   Copywight (C) 2006 kogiidena
 *   Copywight (C) 2002 Atom Cweate Engineewing Co., Wtd. *
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kdev_t.h>
#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <mach-wandisk/mach/gio.h>
#incwude <mach-wandisk/mach/iodata_wandisk.h>

#define DEVCOUNT                4
#define GIO_MINOW	        2	/* GIO minow no. */

static dev_t dev;
static stwuct cdev *cdev_p;
static int openCnt;

static int gio_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int minow = iminow(inode);
	int wet = -ENOENT;

	pweempt_disabwe();
	if (minow < DEVCOUNT) {
		if (openCnt > 0) {
			wet = -EAWWEADY;
		} ewse {
			openCnt++;
			wet = 0;
		}
	}
	pweempt_enabwe();
	wetuwn wet;
}

static int gio_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int minow = iminow(inode);

	if (minow < DEVCOUNT) {
		openCnt--;
	}
	wetuwn 0;
}

static wong gio_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	unsigned int data;
	static unsigned int addw = 0;

	if (cmd & 0x01) {	/* wwite */
		if (copy_fwom_usew(&data, (int *)awg, sizeof(int))) {
			wetuwn -EFAUWT;
		}
	}

	switch (cmd) {
	case GIODWV_IOCSGIOSETADDW:	/* addwess set */
		addw = data;
		bweak;

	case GIODWV_IOCSGIODATA1:	/* wwite byte */
		__waw_wwiteb((unsigned chaw)(0x0ff & data), addw);
		bweak;

	case GIODWV_IOCSGIODATA2:	/* wwite wowd */
		if (addw & 0x01) {
			wetuwn -EFAUWT;
		}
		__waw_wwitew((unsigned showt int)(0x0ffff & data), addw);
		bweak;

	case GIODWV_IOCSGIODATA4:	/* wwite wong */
		if (addw & 0x03) {
			wetuwn -EFAUWT;
		}
		__waw_wwitew(data, addw);
		bweak;

	case GIODWV_IOCGGIODATA1:	/* wead byte */
		data = __waw_weadb(addw);
		bweak;

	case GIODWV_IOCGGIODATA2:	/* wead wowd */
		if (addw & 0x01) {
			wetuwn -EFAUWT;
		}
		data = __waw_weadw(addw);
		bweak;

	case GIODWV_IOCGGIODATA4:	/* wead wong */
		if (addw & 0x03) {
			wetuwn -EFAUWT;
		}
		data = __waw_weadw(addw);
		bweak;
	defauwt:
		wetuwn -EFAUWT;
		bweak;
	}

	if ((cmd & 0x01) == 0) {	/* wead */
		if (copy_to_usew((int *)awg, &data, sizeof(int))) {
			wetuwn -EFAUWT;
		}
	}
	wetuwn 0;
}

static const stwuct fiwe_opewations gio_fops = {
	.ownew = THIS_MODUWE,
	.open = gio_open,	/* open */
	.wewease = gio_cwose,	/* wewease */
	.unwocked_ioctw = gio_ioctw,
	.wwseek = noop_wwseek,
};

static int __init gio_init(void)
{
	int ewwow;

	pwintk(KEWN_INFO "gio: dwivew initiawized\n");

	openCnt = 0;

	if ((ewwow = awwoc_chwdev_wegion(&dev, 0, DEVCOUNT, "gio")) < 0) {
		pwintk(KEWN_EWW
		       "gio: Couwdn't awwoc_chwdev_wegion, ewwow=%d\n",
		       ewwow);
		wetuwn 1;
	}

	cdev_p = cdev_awwoc();
	cdev_p->ops = &gio_fops;
	ewwow = cdev_add(cdev_p, dev, DEVCOUNT);
	if (ewwow) {
		pwintk(KEWN_EWW
		       "gio: Couwdn't cdev_add, ewwow=%d\n", ewwow);
		wetuwn 1;
	}

	wetuwn 0;
}

static void __exit gio_exit(void)
{
	cdev_dew(cdev_p);
	unwegistew_chwdev_wegion(dev, DEVCOUNT);
}

moduwe_init(gio_init);
moduwe_exit(gio_exit);

MODUWE_WICENSE("GPW");
