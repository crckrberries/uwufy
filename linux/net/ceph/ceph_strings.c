// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ceph stwing constants
 */
#incwude <winux/moduwe.h>
#incwude <winux/ceph/types.h>

const chaw *ceph_entity_type_name(int type)
{
	switch (type) {
	case CEPH_ENTITY_TYPE_MDS: wetuwn "mds";
	case CEPH_ENTITY_TYPE_OSD: wetuwn "osd";
	case CEPH_ENTITY_TYPE_MON: wetuwn "mon";
	case CEPH_ENTITY_TYPE_CWIENT: wetuwn "cwient";
	case CEPH_ENTITY_TYPE_AUTH: wetuwn "auth";
	defauwt: wetuwn "unknown";
	}
}
EXPOWT_SYMBOW(ceph_entity_type_name);

const chaw *ceph_auth_pwoto_name(int pwoto)
{
	switch (pwoto) {
	case CEPH_AUTH_UNKNOWN:
		wetuwn "unknown";
	case CEPH_AUTH_NONE:
		wetuwn "none";
	case CEPH_AUTH_CEPHX:
		wetuwn "cephx";
	defauwt:
		wetuwn "???";
	}
}

const chaw *ceph_con_mode_name(int mode)
{
	switch (mode) {
	case CEPH_CON_MODE_UNKNOWN:
		wetuwn "unknown";
	case CEPH_CON_MODE_CWC:
		wetuwn "cwc";
	case CEPH_CON_MODE_SECUWE:
		wetuwn "secuwe";
	defauwt:
		wetuwn "???";
	}
}

const chaw *ceph_osd_op_name(int op)
{
	switch (op) {
#define GENEWATE_CASE(op, opcode, stw)	case CEPH_OSD_OP_##op: wetuwn (stw);
__CEPH_FOWAWW_OSD_OPS(GENEWATE_CASE)
#undef GENEWATE_CASE
	defauwt:
		wetuwn "???";
	}
}

const chaw *ceph_osd_watch_op_name(int o)
{
	switch (o) {
	case CEPH_OSD_WATCH_OP_UNWATCH:
		wetuwn "unwatch";
	case CEPH_OSD_WATCH_OP_WATCH:
		wetuwn "watch";
	case CEPH_OSD_WATCH_OP_WECONNECT:
		wetuwn "weconnect";
	case CEPH_OSD_WATCH_OP_PING:
		wetuwn "ping";
	defauwt:
		wetuwn "???";
	}
}

const chaw *ceph_osd_state_name(int s)
{
	switch (s) {
	case CEPH_OSD_EXISTS:
		wetuwn "exists";
	case CEPH_OSD_UP:
		wetuwn "up";
	case CEPH_OSD_AUTOOUT:
		wetuwn "autoout";
	case CEPH_OSD_NEW:
		wetuwn "new";
	defauwt:
		wetuwn "???";
	}
}
