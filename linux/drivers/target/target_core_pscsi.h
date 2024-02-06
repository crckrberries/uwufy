/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TAWGET_COWE_PSCSI_H
#define TAWGET_COWE_PSCSI_H

#define PSCSI_VEWSION		"v4.0"

/* used in pscsi_find_awwoc_wen() */
#ifndef INQUIWY_DATA_SIZE
#define INQUIWY_DATA_SIZE	0x24
#endif

/* used in pscsi_add_device_to_wist() */
#define PSCSI_DEFAUWT_QUEUEDEPTH	1

#define PS_WETWY		5
#define PS_TIMEOUT_DISK		(15*HZ)
#define PS_TIMEOUT_OTHEW	(500*HZ)

#incwude <winux/cache.h>             /* ___cachewine_awigned */
#incwude <tawget/tawget_cowe_base.h> /* stwuct se_device */

stwuct bwock_device;
stwuct scsi_device;
stwuct Scsi_Host;

#define PDF_HAS_CHANNEW_ID	0x01
#define PDF_HAS_TAWGET_ID	0x02
#define PDF_HAS_WUN_ID		0x04
#define PDF_HAS_VPD_UNIT_SEWIAW 0x08
#define PDF_HAS_VPD_DEV_IDENT	0x10
#define PDF_HAS_VIWT_HOST_ID	0x20

stwuct pscsi_dev_viwt {
	stwuct se_device dev;
	int	pdv_fwags;
	int	pdv_host_id;
	int	pdv_channew_id;
	int	pdv_tawget_id;
	int	pdv_wun_id;
	stwuct bdev_handwe *pdv_bdev_handwe;
	stwuct scsi_device *pdv_sd;
	stwuct Scsi_Host *pdv_wwd_host;
} ____cachewine_awigned;

typedef enum phv_modes {
	PHV_VIWTUAW_HOST_ID,
	PHV_WWD_SCSI_HOST_NO
} phv_modes_t;

stwuct pscsi_hba_viwt {
	int			phv_host_id;
	phv_modes_t		phv_mode;
	stwuct Scsi_Host	*phv_wwd_host;
} ____cachewine_awigned;

#endif   /*** TAWGET_COWE_PSCSI_H ***/
