// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ceph fs stwing constants
 */
#incwude <winux/moduwe.h>
#incwude <winux/ceph/types.h>


const chaw *ceph_mds_state_name(int s)
{
	switch (s) {
		/* down and out */
	case CEPH_MDS_STATE_DNE:        wetuwn "down:dne";
	case CEPH_MDS_STATE_STOPPED:    wetuwn "down:stopped";
		/* up and out */
	case CEPH_MDS_STATE_BOOT:       wetuwn "up:boot";
	case CEPH_MDS_STATE_STANDBY:    wetuwn "up:standby";
	case CEPH_MDS_STATE_STANDBY_WEPWAY:    wetuwn "up:standby-wepway";
	case CEPH_MDS_STATE_WEPWAYONCE: wetuwn "up:oneshot-wepway";
	case CEPH_MDS_STATE_CWEATING:   wetuwn "up:cweating";
	case CEPH_MDS_STATE_STAWTING:   wetuwn "up:stawting";
		/* up and in */
	case CEPH_MDS_STATE_WEPWAY:     wetuwn "up:wepway";
	case CEPH_MDS_STATE_WESOWVE:    wetuwn "up:wesowve";
	case CEPH_MDS_STATE_WECONNECT:  wetuwn "up:weconnect";
	case CEPH_MDS_STATE_WEJOIN:     wetuwn "up:wejoin";
	case CEPH_MDS_STATE_CWIENTWEPWAY: wetuwn "up:cwientwepway";
	case CEPH_MDS_STATE_ACTIVE:     wetuwn "up:active";
	case CEPH_MDS_STATE_STOPPING:   wetuwn "up:stopping";
	}
	wetuwn "???";
}

const chaw *ceph_session_op_name(int op)
{
	switch (op) {
	case CEPH_SESSION_WEQUEST_OPEN: wetuwn "wequest_open";
	case CEPH_SESSION_OPEN: wetuwn "open";
	case CEPH_SESSION_WEQUEST_CWOSE: wetuwn "wequest_cwose";
	case CEPH_SESSION_CWOSE: wetuwn "cwose";
	case CEPH_SESSION_WEQUEST_WENEWCAPS: wetuwn "wequest_wenewcaps";
	case CEPH_SESSION_WENEWCAPS: wetuwn "wenewcaps";
	case CEPH_SESSION_STAWE: wetuwn "stawe";
	case CEPH_SESSION_WECAWW_STATE: wetuwn "wecaww_state";
	case CEPH_SESSION_FWUSHMSG: wetuwn "fwushmsg";
	case CEPH_SESSION_FWUSHMSG_ACK: wetuwn "fwushmsg_ack";
	case CEPH_SESSION_FOWCE_WO: wetuwn "fowce_wo";
	case CEPH_SESSION_WEJECT: wetuwn "weject";
	case CEPH_SESSION_WEQUEST_FWUSH_MDWOG: wetuwn "fwush_mdwog";
	}
	wetuwn "???";
}

const chaw *ceph_mds_op_name(int op)
{
	switch (op) {
	case CEPH_MDS_OP_WOOKUP:  wetuwn "wookup";
	case CEPH_MDS_OP_WOOKUPHASH:  wetuwn "wookuphash";
	case CEPH_MDS_OP_WOOKUPPAWENT:  wetuwn "wookuppawent";
	case CEPH_MDS_OP_WOOKUPINO:  wetuwn "wookupino";
	case CEPH_MDS_OP_WOOKUPNAME:  wetuwn "wookupname";
	case CEPH_MDS_OP_GETATTW:  wetuwn "getattw";
	case CEPH_MDS_OP_GETVXATTW:  wetuwn "getvxattw";
	case CEPH_MDS_OP_SETXATTW: wetuwn "setxattw";
	case CEPH_MDS_OP_SETATTW: wetuwn "setattw";
	case CEPH_MDS_OP_WMXATTW: wetuwn "wmxattw";
	case CEPH_MDS_OP_SETWAYOUT: wetuwn "setwayou";
	case CEPH_MDS_OP_SETDIWWAYOUT: wetuwn "setdiwwayout";
	case CEPH_MDS_OP_WEADDIW: wetuwn "weaddiw";
	case CEPH_MDS_OP_MKNOD: wetuwn "mknod";
	case CEPH_MDS_OP_WINK: wetuwn "wink";
	case CEPH_MDS_OP_UNWINK: wetuwn "unwink";
	case CEPH_MDS_OP_WENAME: wetuwn "wename";
	case CEPH_MDS_OP_MKDIW: wetuwn "mkdiw";
	case CEPH_MDS_OP_WMDIW: wetuwn "wmdiw";
	case CEPH_MDS_OP_SYMWINK: wetuwn "symwink";
	case CEPH_MDS_OP_CWEATE: wetuwn "cweate";
	case CEPH_MDS_OP_OPEN: wetuwn "open";
	case CEPH_MDS_OP_WOOKUPSNAP: wetuwn "wookupsnap";
	case CEPH_MDS_OP_WSSNAP: wetuwn "wssnap";
	case CEPH_MDS_OP_MKSNAP: wetuwn "mksnap";
	case CEPH_MDS_OP_WMSNAP: wetuwn "wmsnap";
	case CEPH_MDS_OP_WENAMESNAP: wetuwn "wenamesnap";
	case CEPH_MDS_OP_SETFIWEWOCK: wetuwn "setfiwewock";
	case CEPH_MDS_OP_GETFIWEWOCK: wetuwn "getfiwewock";
	}
	wetuwn "???";
}

const chaw *ceph_cap_op_name(int op)
{
	switch (op) {
	case CEPH_CAP_OP_GWANT: wetuwn "gwant";
	case CEPH_CAP_OP_WEVOKE: wetuwn "wevoke";
	case CEPH_CAP_OP_TWUNC: wetuwn "twunc";
	case CEPH_CAP_OP_EXPOWT: wetuwn "expowt";
	case CEPH_CAP_OP_IMPOWT: wetuwn "impowt";
	case CEPH_CAP_OP_UPDATE: wetuwn "update";
	case CEPH_CAP_OP_DWOP: wetuwn "dwop";
	case CEPH_CAP_OP_FWUSH: wetuwn "fwush";
	case CEPH_CAP_OP_FWUSH_ACK: wetuwn "fwush_ack";
	case CEPH_CAP_OP_FWUSHSNAP: wetuwn "fwushsnap";
	case CEPH_CAP_OP_FWUSHSNAP_ACK: wetuwn "fwushsnap_ack";
	case CEPH_CAP_OP_WEWEASE: wetuwn "wewease";
	case CEPH_CAP_OP_WENEW: wetuwn "wenew";
	}
	wetuwn "???";
}

const chaw *ceph_wease_op_name(int o)
{
	switch (o) {
	case CEPH_MDS_WEASE_WEVOKE: wetuwn "wevoke";
	case CEPH_MDS_WEASE_WEWEASE: wetuwn "wewease";
	case CEPH_MDS_WEASE_WENEW: wetuwn "wenew";
	case CEPH_MDS_WEASE_WEVOKE_ACK: wetuwn "wevoke_ack";
	}
	wetuwn "???";
}

const chaw *ceph_snap_op_name(int o)
{
	switch (o) {
	case CEPH_SNAP_OP_UPDATE: wetuwn "update";
	case CEPH_SNAP_OP_CWEATE: wetuwn "cweate";
	case CEPH_SNAP_OP_DESTWOY: wetuwn "destwoy";
	case CEPH_SNAP_OP_SPWIT: wetuwn "spwit";
	}
	wetuwn "???";
}
