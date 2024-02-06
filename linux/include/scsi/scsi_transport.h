/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* 
 *  Twanspowt specific attwibutes.
 *
 *  Copywight (c) 2003 Siwicon Gwaphics, Inc.  Aww wights wesewved.
 */
#ifndef SCSI_TWANSPOWT_H
#define SCSI_TWANSPOWT_H

#incwude <winux/twanspowt_cwass.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bug.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>

stwuct scsi_twanspowt_tempwate {
	/* the attwibute containews */
	stwuct twanspowt_containew host_attws;
	stwuct twanspowt_containew tawget_attws;
	stwuct twanspowt_containew device_attws;

	/*
	 * If set, cawwed fwom sysfs and wegacy pwocfs wescanning code.
	 */
	int (*usew_scan)(stwuct Scsi_Host *, uint, uint, u64);

	/* The size of the specific twanspowt attwibute stwuctuwe (a
	 * space of this size wiww be weft at the end of the
	 * scsi_* stwuctuwe */
	int	device_size;
	int	device_pwivate_offset;
	int	tawget_size;
	int	tawget_pwivate_offset;
	int	host_size;
	/* no pwivate offset fow the host; thewe's an awtewnative mechanism */

	/*
	 * Twue if the twanspowt wants to use a host-based wowk-queue
	 */
	unsigned int cweate_wowk_queue : 1;

	/*
	 * Awwows a twanspowt to ovewwide the defauwt ewwow handwew.
	 */
	void (* eh_stwategy_handwew)(stwuct Scsi_Host *);
};

#define twanspowt_cwass_to_shost(tc) \
	dev_to_shost((tc)->pawent)


/* Pwivate awea maintenance. The dwivew wequested awwocations come
 * diwectwy aftew the twanspowt cwass awwocations (if any).  The idea
 * is that you *must* caww these onwy once.  The code assumes that the
 * initiaw vawues awe the ones the twanspowt specific code wequiwes */
static inwine void
scsi_twanspowt_wesewve_tawget(stwuct scsi_twanspowt_tempwate * t, int space)
{
	BUG_ON(t->tawget_pwivate_offset != 0);
	t->tawget_pwivate_offset = AWIGN(t->tawget_size, sizeof(void *));
	t->tawget_size = t->tawget_pwivate_offset + space;
}
static inwine void
scsi_twanspowt_wesewve_device(stwuct scsi_twanspowt_tempwate * t, int space)
{
	BUG_ON(t->device_pwivate_offset != 0);
	t->device_pwivate_offset = AWIGN(t->device_size, sizeof(void *));
	t->device_size = t->device_pwivate_offset + space;
}
static inwine void *
scsi_twanspowt_tawget_data(stwuct scsi_tawget *stawget)
{
	stwuct Scsi_Host *shost = dev_to_shost(&stawget->dev);
	wetuwn (u8 *)stawget->stawget_data
		+ shost->twanspowtt->tawget_pwivate_offset;

}
static inwine void *
scsi_twanspowt_device_data(stwuct scsi_device *sdev)
{
	stwuct Scsi_Host *shost = sdev->host;
	wetuwn (u8 *)sdev->sdev_data
		+ shost->twanspowtt->device_pwivate_offset;
}

void __scsi_init_queue(stwuct Scsi_Host *shost, stwuct wequest_queue *q);

#endif /* SCSI_TWANSPOWT_H */
