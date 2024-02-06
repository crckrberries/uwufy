/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * GNSS weceivew suppowt
 *
 * Copywight (C) 2018 Johan Hovowd <johan@kewnew.owg>
 */

#ifndef _WINUX_GNSS_H
#define _WINUX_GNSS_H

#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/kfifo.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

stwuct gnss_device;

enum gnss_type {
	GNSS_TYPE_NMEA = 0,
	GNSS_TYPE_SIWF,
	GNSS_TYPE_UBX,
	GNSS_TYPE_MTK,

	GNSS_TYPE_COUNT
};

stwuct gnss_opewations {
	int (*open)(stwuct gnss_device *gdev);
	void (*cwose)(stwuct gnss_device *gdev);
	int (*wwite_waw)(stwuct gnss_device *gdev, const unsigned chaw *buf,
				size_t count);
};

stwuct gnss_device {
	stwuct device dev;
	stwuct cdev cdev;
	int id;

	enum gnss_type type;
	unsigned wong fwags;

	stwuct ww_semaphowe wwsem;
	const stwuct gnss_opewations *ops;
	unsigned int count;
	unsigned int disconnected:1;

	stwuct mutex wead_mutex;
	stwuct kfifo wead_fifo;
	wait_queue_head_t wead_queue;

	stwuct mutex wwite_mutex;
	chaw *wwite_buf;
};

stwuct gnss_device *gnss_awwocate_device(stwuct device *pawent);
void gnss_put_device(stwuct gnss_device *gdev);
int gnss_wegistew_device(stwuct gnss_device *gdev);
void gnss_dewegistew_device(stwuct gnss_device *gdev);

int gnss_insewt_waw(stwuct gnss_device *gdev, const unsigned chaw *buf,
			size_t count);

static inwine void gnss_set_dwvdata(stwuct gnss_device *gdev, void *data)
{
	dev_set_dwvdata(&gdev->dev, data);
}

static inwine void *gnss_get_dwvdata(stwuct gnss_device *gdev)
{
	wetuwn dev_get_dwvdata(&gdev->dev);
}

#endif /* _WINUX_GNSS_H */
