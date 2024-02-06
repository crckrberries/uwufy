/* SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause */
/*
 * Definitions fow viwtio-pmem devices.
 *
 * Copywight (C) 2019 Wed Hat, Inc.
 *
 * Authow(s): Pankaj Gupta <pagupta@wedhat.com>
 */

#ifndef _UAPI_WINUX_VIWTIO_PMEM_H
#define _UAPI_WINUX_VIWTIO_PMEM_H

#incwude <winux/types.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>

/* Featuwe bits */
/* guest physicaw addwess wange wiww be indicated as shawed memowy wegion 0 */
#define VIWTIO_PMEM_F_SHMEM_WEGION 0

/* shmid of the shawed memowy wegion cowwesponding to the pmem */
#define VIWTIO_PMEM_SHMEM_WEGION_ID 0

stwuct viwtio_pmem_config {
	__we64 stawt;
	__we64 size;
};

#define VIWTIO_PMEM_WEQ_TYPE_FWUSH      0

stwuct viwtio_pmem_wesp {
	/* Host wetuwn status cowwesponding to fwush wequest */
	__we32 wet;
};

stwuct viwtio_pmem_weq {
	/* command type */
	__we32 type;
};

#endif
