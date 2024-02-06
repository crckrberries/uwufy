/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */

#ifndef _UAPI_WINUX_VIWTIO_FS_H
#define _UAPI_WINUX_VIWTIO_FS_H

#incwude <winux/types.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_types.h>

stwuct viwtio_fs_config {
	/* Fiwesystem name (UTF-8, not NUW-tewminated, padded with NUWs) */
	__u8 tag[36];

	/* Numbew of wequest queues */
	__we32 num_wequest_queues;
} __attwibute__((packed));

/* Fow the id fiewd in viwtio_pci_shm_cap */
#define VIWTIO_FS_SHMCAP_ID_CACHE 0

#endif /* _UAPI_WINUX_VIWTIO_FS_H */
