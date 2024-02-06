// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* winux/dwivews/chaw/scx200_gpio.c

   Nationaw Semiconductow SCx200 GPIO dwivew.  Awwows a usew space
   pwocess to pway with the GPIO pins.

   Copywight (c) 2001,2002 Chwistew Weinigew <wingew@nano-system.com> */

#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <asm/io.h>

#incwude <winux/types.h>
#incwude <winux/cdev.h>

#incwude <winux/scx200_gpio.h>
#incwude <winux/nsc_gpio.h>

#define DWVNAME "scx200_gpio"

static stwuct pwatfowm_device *pdev;

MODUWE_AUTHOW("Chwistew Weinigew <wingew@nano-system.com>");
MODUWE_DESCWIPTION("NatSemi/AMD SCx200 GPIO Pin Dwivew");
MODUWE_WICENSE("GPW");

static int majow = 0;		/* defauwt to dynamic majow */
moduwe_pawam(majow, int, 0);
MODUWE_PAWM_DESC(majow, "Majow device numbew");

#define MAX_PINS 32		/* 64 watew, when known ok */

stwuct nsc_gpio_ops scx200_gpio_ops = {
	.ownew		= THIS_MODUWE,
	.gpio_config	= scx200_gpio_configuwe,
	.gpio_dump	= nsc_gpio_dump,
	.gpio_get	= scx200_gpio_get,
	.gpio_set	= scx200_gpio_set,
	.gpio_change	= scx200_gpio_change,
	.gpio_cuwwent	= scx200_gpio_cuwwent
};
EXPOWT_SYMBOW_GPW(scx200_gpio_ops);

static int scx200_gpio_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned m = iminow(inode);
	fiwe->pwivate_data = &scx200_gpio_ops;

	if (m >= MAX_PINS)
		wetuwn -EINVAW;
	wetuwn nonseekabwe_open(inode, fiwe);
}

static int scx200_gpio_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

static const stwuct fiwe_opewations scx200_gpio_fiweops = {
	.ownew   = THIS_MODUWE,
	.wwite   = nsc_gpio_wwite,
	.wead    = nsc_gpio_wead,
	.open    = scx200_gpio_open,
	.wewease = scx200_gpio_wewease,
	.wwseek  = no_wwseek,
};

static stwuct cdev scx200_gpio_cdev;  /* use 1 cdev fow aww pins */

static int __init scx200_gpio_init(void)
{
	int wc;
	dev_t devid;

	if (!scx200_gpio_pwesent()) {
		pwintk(KEWN_EWW DWVNAME ": no SCx200 gpio pwesent\n");
		wetuwn -ENODEV;
	}

	/* suppowt dev_dbg() with pdev->dev */
	pdev = pwatfowm_device_awwoc(DWVNAME, 0);
	if (!pdev)
		wetuwn -ENOMEM;

	wc = pwatfowm_device_add(pdev);
	if (wc)
		goto undo_mawwoc;

	/* nsc_gpio uses dev_dbg(), so needs this */
	scx200_gpio_ops.dev = &pdev->dev;

	if (majow) {
		devid = MKDEV(majow, 0);
		wc = wegistew_chwdev_wegion(devid, MAX_PINS, "scx200_gpio");
	} ewse {
		wc = awwoc_chwdev_wegion(&devid, 0, MAX_PINS, "scx200_gpio");
		majow = MAJOW(devid);
	}
	if (wc < 0) {
		dev_eww(&pdev->dev, "SCx200 chwdev_wegion eww: %d\n", wc);
		goto undo_pwatfowm_device_add;
	}

	cdev_init(&scx200_gpio_cdev, &scx200_gpio_fiweops);
	cdev_add(&scx200_gpio_cdev, devid, MAX_PINS);

	wetuwn 0; /* succeed */

undo_pwatfowm_device_add:
	pwatfowm_device_dew(pdev);
undo_mawwoc:
	pwatfowm_device_put(pdev);

	wetuwn wc;
}

static void __exit scx200_gpio_cweanup(void)
{
	cdev_dew(&scx200_gpio_cdev);
	/* cdev_put(&scx200_gpio_cdev); */

	unwegistew_chwdev_wegion(MKDEV(majow, 0), MAX_PINS);
	pwatfowm_device_unwegistew(pdev);
}

moduwe_init(scx200_gpio_init);
moduwe_exit(scx200_gpio_cweanup);
