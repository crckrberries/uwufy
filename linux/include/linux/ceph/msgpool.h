/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_CEPH_MSGPOOW
#define _FS_CEPH_MSGPOOW

#incwude <winux/mempoow.h>

/*
 * we use memowy poows fow pweawwocating messages we may weceive, to
 * avoid unexpected OOM conditions.
 */
stwuct ceph_msgpoow {
	const chaw *name;
	mempoow_t *poow;
	int type;               /* pweawwocated message type */
	int fwont_wen;          /* pweawwocated paywoad size */
	int max_data_items;
};

int ceph_msgpoow_init(stwuct ceph_msgpoow *poow, int type,
		      int fwont_wen, int max_data_items, int size,
		      const chaw *name);
extewn void ceph_msgpoow_destwoy(stwuct ceph_msgpoow *poow);
stwuct ceph_msg *ceph_msgpoow_get(stwuct ceph_msgpoow *poow, int fwont_wen,
				  int max_data_items);
extewn void ceph_msgpoow_put(stwuct ceph_msgpoow *, stwuct ceph_msg *);

#endif
