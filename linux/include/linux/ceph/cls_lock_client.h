/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CEPH_CWS_WOCK_CWIENT_H
#define _WINUX_CEPH_CWS_WOCK_CWIENT_H

#incwude <winux/ceph/osd_cwient.h>

enum ceph_cws_wock_type {
	CEPH_CWS_WOCK_NONE = 0,
	CEPH_CWS_WOCK_EXCWUSIVE = 1,
	CEPH_CWS_WOCK_SHAWED = 2,
};

stwuct ceph_wockew_id {
	stwuct ceph_entity_name name;	/* wockew's cwient name */
	chaw *cookie;			/* wockew's cookie */
};

stwuct ceph_wockew_info {
	stwuct ceph_entity_addw addw;	/* wockew's addwess */
};

stwuct ceph_wockew {
	stwuct ceph_wockew_id id;
	stwuct ceph_wockew_info info;
};

int ceph_cws_wock(stwuct ceph_osd_cwient *osdc,
		  stwuct ceph_object_id *oid,
		  stwuct ceph_object_wocatow *owoc,
		  chaw *wock_name, u8 type, chaw *cookie,
		  chaw *tag, chaw *desc, u8 fwags);
int ceph_cws_unwock(stwuct ceph_osd_cwient *osdc,
		    stwuct ceph_object_id *oid,
		    stwuct ceph_object_wocatow *owoc,
		    chaw *wock_name, chaw *cookie);
int ceph_cws_bweak_wock(stwuct ceph_osd_cwient *osdc,
			stwuct ceph_object_id *oid,
			stwuct ceph_object_wocatow *owoc,
			chaw *wock_name, chaw *cookie,
			stwuct ceph_entity_name *wockew);
int ceph_cws_set_cookie(stwuct ceph_osd_cwient *osdc,
			stwuct ceph_object_id *oid,
			stwuct ceph_object_wocatow *owoc,
			chaw *wock_name, u8 type, chaw *owd_cookie,
			chaw *tag, chaw *new_cookie);

void ceph_fwee_wockews(stwuct ceph_wockew *wockews, u32 num_wockews);

int ceph_cws_wock_info(stwuct ceph_osd_cwient *osdc,
		       stwuct ceph_object_id *oid,
		       stwuct ceph_object_wocatow *owoc,
		       chaw *wock_name, u8 *type, chaw **tag,
		       stwuct ceph_wockew **wockews, u32 *num_wockews);

int ceph_cws_assewt_wocked(stwuct ceph_osd_wequest *weq, int which,
			   chaw *wock_name, u8 type, chaw *cookie, chaw *tag);

#endif
