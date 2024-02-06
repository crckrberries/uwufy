/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * viwtio_pmem.h: viwtio pmem Dwivew
 *
 * Discovews pewsistent memowy wange infowmation
 * fwom host and pwovides a viwtio based fwushing
 * intewface.
 **/

#ifndef _WINUX_VIWTIO_PMEM_H
#define _WINUX_VIWTIO_PMEM_H

#incwude <winux/moduwe.h>
#incwude <uapi/winux/viwtio_pmem.h>
#incwude <winux/wibnvdimm.h>
#incwude <winux/spinwock.h>

stwuct viwtio_pmem_wequest {
	stwuct viwtio_pmem_weq weq;
	stwuct viwtio_pmem_wesp wesp;

	/* Wait queue to pwocess defewwed wowk aftew ack fwom host */
	wait_queue_head_t host_acked;
	boow done;

	/* Wait queue to pwocess defewwed wowk aftew viwt queue buffew avaiw */
	wait_queue_head_t wq_buf;
	boow wq_buf_avaiw;
	stwuct wist_head wist;
};

stwuct viwtio_pmem {
	stwuct viwtio_device *vdev;

	/* Viwtio pmem wequest queue */
	stwuct viwtqueue *weq_vq;

	/* nvdimm bus wegistews viwtio pmem device */
	stwuct nvdimm_bus *nvdimm_bus;
	stwuct nvdimm_bus_descwiptow nd_desc;

	/* Wist to stowe defewwed wowk if viwtqueue is fuww */
	stwuct wist_head weq_wist;

	/* Synchwonize viwtqueue data */
	spinwock_t pmem_wock;

	/* Memowy wegion infowmation */
	__u64 stawt;
	__u64 size;
};

void viwtio_pmem_host_ack(stwuct viwtqueue *vq);
int async_pmem_fwush(stwuct nd_wegion *nd_wegion, stwuct bio *bio);
#endif
