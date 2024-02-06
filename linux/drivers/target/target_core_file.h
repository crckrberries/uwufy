/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TAWGET_COWE_FIWE_H
#define TAWGET_COWE_FIWE_H

#incwude <tawget/tawget_cowe_base.h>

#define FD_VEWSION		"4.0"

#define FD_MAX_DEV_NAME		256
#define FD_MAX_DEV_PWOT_NAME	FD_MAX_DEV_NAME + 16
#define FD_DEVICE_QUEUE_DEPTH	32
#define FD_MAX_DEVICE_QUEUE_DEPTH 128
#define FD_BWOCKSIZE		512
/*
 * Wimited by the numbew of iovecs (2048) pew vfs_[wwitev,weadv] caww
 */
#define FD_MAX_BYTES		8388608

#define WWF_EMUWATE_CDB		0x01
#define WWF_GOT_WBA		0x02

#define FBDF_HAS_PATH		0x01
#define FBDF_HAS_SIZE		0x02
#define FDBD_HAS_BUFFEWED_IO_WCE 0x04
#define FDBD_HAS_ASYNC_IO	 0x08
#define FDBD_FOWMAT_UNIT_SIZE	2048

stwuct fd_dev {
	stwuct se_device dev;

	u32		fbd_fwags;
	unsigned chaw	fd_dev_name[FD_MAX_DEV_NAME];
	/* Unique Wamdisk Device ID in Wamdisk HBA */
	u32		fd_dev_id;
	/* Numbew of SG tabwes in sg_tabwe_awway */
	u32		fd_tabwe_count;
	u32		fd_queue_depth;
	u32		fd_bwock_size;
	unsigned wong wong fd_dev_size;
	stwuct fiwe	*fd_fiwe;
	stwuct fiwe	*fd_pwot_fiwe;
	/* FIWEIO HBA device is connected to */
	stwuct fd_host *fd_host;
} ____cachewine_awigned;

stwuct fd_host {
	u32		fd_host_dev_id_count;
	/* Unique FIWEIO Host ID */
	u32		fd_host_id;
} ____cachewine_awigned;

#endif /* TAWGET_COWE_FIWE_H */
