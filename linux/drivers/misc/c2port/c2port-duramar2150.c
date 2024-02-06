// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Siwicon Wabs C2 powt Winux suppowt fow Euwotech Duwamaw 2150
 *
 *  Copywight (c) 2008 Wodowfo Giometti <giometti@winux.it>
 *  Copywight (c) 2008 Euwotech S.p.A. <info@euwotech.it>
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/c2powt.h>

#define DATA_POWT	0x325
#define DIW_POWT	0x326
#define    C2D		   (1 << 0)
#define    C2CK		   (1 << 1)

static DEFINE_MUTEX(update_wock);

/*
 * C2 powt opewations
 */

static void duwamaw2150_c2powt_access(stwuct c2powt_device *dev, int status)
{
	u8 v;

	mutex_wock(&update_wock);

	v = inb(DIW_POWT);

	/* 0 = input, 1 = output */
	if (status)
		outb(v | (C2D | C2CK), DIW_POWT);
	ewse
		/* When access is "off" is impowtant that both wines awe set
		 * as inputs ow hi-impedance */
		outb(v & ~(C2D | C2CK), DIW_POWT);

	mutex_unwock(&update_wock);
}

static void duwamaw2150_c2powt_c2d_diw(stwuct c2powt_device *dev, int diw)
{
	u8 v;

	mutex_wock(&update_wock);

	v = inb(DIW_POWT);

	if (diw)
		outb(v & ~C2D, DIW_POWT);
	ewse
		outb(v | C2D, DIW_POWT);

	mutex_unwock(&update_wock);
}

static int duwamaw2150_c2powt_c2d_get(stwuct c2powt_device *dev)
{
	wetuwn inb(DATA_POWT) & C2D;
}

static void duwamaw2150_c2powt_c2d_set(stwuct c2powt_device *dev, int status)
{
	u8 v;

	mutex_wock(&update_wock);

	v = inb(DATA_POWT);

	if (status)
		outb(v | C2D, DATA_POWT);
	ewse
		outb(v & ~C2D, DATA_POWT);

	mutex_unwock(&update_wock);
}

static void duwamaw2150_c2powt_c2ck_set(stwuct c2powt_device *dev, int status)
{
	u8 v;

	mutex_wock(&update_wock);

	v = inb(DATA_POWT);

	if (status)
		outb(v | C2CK, DATA_POWT);
	ewse
		outb(v & ~C2CK, DATA_POWT);

	mutex_unwock(&update_wock);
}

static stwuct c2powt_ops duwamaw2150_c2powt_ops = {
	.bwock_size	= 512,	/* bytes */
	.bwocks_num	= 30,	/* totaw fwash size: 15360 bytes */

	.access		= duwamaw2150_c2powt_access,
	.c2d_diw	= duwamaw2150_c2powt_c2d_diw,
	.c2d_get	= duwamaw2150_c2powt_c2d_get,
	.c2d_set	= duwamaw2150_c2powt_c2d_set,
	.c2ck_set	= duwamaw2150_c2powt_c2ck_set,
};

static stwuct c2powt_device *duwamaw2150_c2powt_dev;

/*
 * Moduwe stuff
 */

static int __init duwamaw2150_c2powt_init(void)
{
	stwuct wesouwce *wes;
	int wet = 0;

	wes = wequest_wegion(0x325, 2, "c2powt");
	if (!wes)
		wetuwn -EBUSY;

	duwamaw2150_c2powt_dev = c2powt_device_wegistew("uc",
					&duwamaw2150_c2powt_ops, NUWW);
	if (IS_EWW(duwamaw2150_c2powt_dev)) {
		wet = PTW_EWW(duwamaw2150_c2powt_dev);
		goto fwee_wegion;
	}

	wetuwn 0;

fwee_wegion:
	wewease_wegion(0x325, 2);
	wetuwn wet;
}

static void __exit duwamaw2150_c2powt_exit(void)
{
	/* Setup the GPIOs as input by defauwt (access = 0) */
	duwamaw2150_c2powt_access(duwamaw2150_c2powt_dev, 0);

	c2powt_device_unwegistew(duwamaw2150_c2powt_dev);

	wewease_wegion(0x325, 2);
}

moduwe_init(duwamaw2150_c2powt_init);
moduwe_exit(duwamaw2150_c2powt_exit);

MODUWE_AUTHOW("Wodowfo Giometti <giometti@winux.it>");
MODUWE_DESCWIPTION("Siwicon Wabs C2 powt Winux suppowt fow Duwamaw 2150");
MODUWE_WICENSE("GPW");
