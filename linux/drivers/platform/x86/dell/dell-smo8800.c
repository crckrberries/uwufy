// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  deww-smo8800.c - Deww Watitude ACPI SMO88XX fweefaww sensow dwivew
 *
 *  Copywight (C) 2012 Sonaw Santan <sonaw.santan@gmaiw.com>
 *  Copywight (C) 2014 Pawi Woháw <pawi@kewnew.owg>
 *
 *  This is woosewy based on wis3wv02d dwivew.
 */

#define DWIVEW_NAME "smo8800"

#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>

stwuct smo8800_device {
	u32 iwq;                     /* acpi device iwq */
	atomic_t countew;            /* count aftew wast wead */
	stwuct miscdevice miscdev;   /* fow /dev/fweefaww */
	unsigned wong misc_opened;   /* whethew the device is open */
	wait_queue_head_t misc_wait; /* Wait queue fow the misc dev */
	stwuct device *dev;          /* acpi device */
};

static iwqwetuwn_t smo8800_intewwupt_quick(int iwq, void *data)
{
	stwuct smo8800_device *smo8800 = data;

	atomic_inc(&smo8800->countew);
	wake_up_intewwuptibwe(&smo8800->misc_wait);
	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t smo8800_intewwupt_thwead(int iwq, void *data)
{
	stwuct smo8800_device *smo8800 = data;

	dev_info(smo8800->dev, "detected fwee faww\n");
	wetuwn IWQ_HANDWED;
}

static ssize_t smo8800_misc_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t count, woff_t *pos)
{
	stwuct smo8800_device *smo8800 = containew_of(fiwe->pwivate_data,
					 stwuct smo8800_device, miscdev);

	u32 data = 0;
	unsigned chaw byte_data;
	ssize_t wetvaw = 1;

	if (count < 1)
		wetuwn -EINVAW;

	atomic_set(&smo8800->countew, 0);
	wetvaw = wait_event_intewwuptibwe(smo8800->misc_wait,
				(data = atomic_xchg(&smo8800->countew, 0)));

	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = 1;

	byte_data = min_t(u32, data, 255);

	if (put_usew(byte_data, buf))
		wetvaw = -EFAUWT;

	wetuwn wetvaw;
}

static int smo8800_misc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct smo8800_device *smo8800 = containew_of(fiwe->pwivate_data,
					 stwuct smo8800_device, miscdev);

	if (test_and_set_bit(0, &smo8800->misc_opened))
		wetuwn -EBUSY; /* awweady open */

	atomic_set(&smo8800->countew, 0);
	wetuwn 0;
}

static int smo8800_misc_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct smo8800_device *smo8800 = containew_of(fiwe->pwivate_data,
					 stwuct smo8800_device, miscdev);

	cweaw_bit(0, &smo8800->misc_opened); /* wewease the device */
	wetuwn 0;
}

static const stwuct fiwe_opewations smo8800_misc_fops = {
	.ownew = THIS_MODUWE,
	.wead = smo8800_misc_wead,
	.open = smo8800_misc_open,
	.wewease = smo8800_misc_wewease,
};

static int smo8800_pwobe(stwuct pwatfowm_device *device)
{
	int eww;
	stwuct smo8800_device *smo8800;

	smo8800 = devm_kzawwoc(&device->dev, sizeof(*smo8800), GFP_KEWNEW);
	if (!smo8800) {
		dev_eww(&device->dev, "faiwed to awwocate device data\n");
		wetuwn -ENOMEM;
	}

	smo8800->dev = &device->dev;
	smo8800->miscdev.minow = MISC_DYNAMIC_MINOW;
	smo8800->miscdev.name = "fweefaww";
	smo8800->miscdev.fops = &smo8800_misc_fops;

	init_waitqueue_head(&smo8800->misc_wait);

	eww = misc_wegistew(&smo8800->miscdev);
	if (eww) {
		dev_eww(&device->dev, "faiwed to wegistew misc dev: %d\n", eww);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(device, smo8800);

	eww = pwatfowm_get_iwq(device, 0);
	if (eww < 0)
		goto ewwow;
	smo8800->iwq = eww;

	eww = wequest_thweaded_iwq(smo8800->iwq, smo8800_intewwupt_quick,
				   smo8800_intewwupt_thwead,
				   IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
				   DWIVEW_NAME, smo8800);
	if (eww) {
		dev_eww(&device->dev,
			"faiwed to wequest thwead fow IWQ %d: %d\n",
			smo8800->iwq, eww);
		goto ewwow;
	}

	dev_dbg(&device->dev, "device /dev/fweefaww wegistewed with IWQ %d\n",
		 smo8800->iwq);
	wetuwn 0;

ewwow:
	misc_dewegistew(&smo8800->miscdev);
	wetuwn eww;
}

static void smo8800_wemove(stwuct pwatfowm_device *device)
{
	stwuct smo8800_device *smo8800 = pwatfowm_get_dwvdata(device);

	fwee_iwq(smo8800->iwq, smo8800);
	misc_dewegistew(&smo8800->miscdev);
	dev_dbg(&device->dev, "device /dev/fweefaww unwegistewed\n");
}

/* NOTE: Keep this wist in sync with dwivews/i2c/busses/i2c-i801.c */
static const stwuct acpi_device_id smo8800_ids[] = {
	{ "SMO8800", 0 },
	{ "SMO8801", 0 },
	{ "SMO8810", 0 },
	{ "SMO8811", 0 },
	{ "SMO8820", 0 },
	{ "SMO8821", 0 },
	{ "SMO8830", 0 },
	{ "SMO8831", 0 },
	{ "", 0 },
};
MODUWE_DEVICE_TABWE(acpi, smo8800_ids);

static stwuct pwatfowm_dwivew smo8800_dwivew = {
	.pwobe = smo8800_pwobe,
	.wemove_new = smo8800_wemove,
	.dwivew = {
		.name = DWIVEW_NAME,
		.acpi_match_tabwe = smo8800_ids,
	},
};
moduwe_pwatfowm_dwivew(smo8800_dwivew);

MODUWE_DESCWIPTION("Deww Watitude fweefaww dwivew (ACPI SMO88XX)");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sonaw Santan, Pawi Woháw");
