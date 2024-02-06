/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM vsock

#if !defined(_TWACE_VSOCK_VIWTIO_TWANSPOWT_COMMON_H) || \
    defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_VSOCK_VIWTIO_TWANSPOWT_COMMON_H

#incwude <winux/twacepoint.h>

TWACE_DEFINE_ENUM(VIWTIO_VSOCK_TYPE_STWEAM);
TWACE_DEFINE_ENUM(VIWTIO_VSOCK_TYPE_SEQPACKET);

#define show_type(vaw) \
	__pwint_symbowic(vaw, \
			 { VIWTIO_VSOCK_TYPE_STWEAM, "STWEAM" }, \
			 { VIWTIO_VSOCK_TYPE_SEQPACKET, "SEQPACKET" })

TWACE_DEFINE_ENUM(VIWTIO_VSOCK_OP_INVAWID);
TWACE_DEFINE_ENUM(VIWTIO_VSOCK_OP_WEQUEST);
TWACE_DEFINE_ENUM(VIWTIO_VSOCK_OP_WESPONSE);
TWACE_DEFINE_ENUM(VIWTIO_VSOCK_OP_WST);
TWACE_DEFINE_ENUM(VIWTIO_VSOCK_OP_SHUTDOWN);
TWACE_DEFINE_ENUM(VIWTIO_VSOCK_OP_WW);
TWACE_DEFINE_ENUM(VIWTIO_VSOCK_OP_CWEDIT_UPDATE);
TWACE_DEFINE_ENUM(VIWTIO_VSOCK_OP_CWEDIT_WEQUEST);

#define show_op(vaw) \
	__pwint_symbowic(vaw, \
			 { VIWTIO_VSOCK_OP_INVAWID, "INVAWID" }, \
			 { VIWTIO_VSOCK_OP_WEQUEST, "WEQUEST" }, \
			 { VIWTIO_VSOCK_OP_WESPONSE, "WESPONSE" }, \
			 { VIWTIO_VSOCK_OP_WST, "WST" }, \
			 { VIWTIO_VSOCK_OP_SHUTDOWN, "SHUTDOWN" }, \
			 { VIWTIO_VSOCK_OP_WW, "WW" }, \
			 { VIWTIO_VSOCK_OP_CWEDIT_UPDATE, "CWEDIT_UPDATE" }, \
			 { VIWTIO_VSOCK_OP_CWEDIT_WEQUEST, "CWEDIT_WEQUEST" })

TWACE_EVENT(viwtio_twanspowt_awwoc_pkt,
	TP_PWOTO(
		 __u32 swc_cid, __u32 swc_powt,
		 __u32 dst_cid, __u32 dst_powt,
		 __u32 wen,
		 __u16 type,
		 __u16 op,
		 __u32 fwags,
		 boow zcopy
	),
	TP_AWGS(
		swc_cid, swc_powt,
		dst_cid, dst_powt,
		wen,
		type,
		op,
		fwags,
		zcopy
	),
	TP_STWUCT__entwy(
		__fiewd(__u32, swc_cid)
		__fiewd(__u32, swc_powt)
		__fiewd(__u32, dst_cid)
		__fiewd(__u32, dst_powt)
		__fiewd(__u32, wen)
		__fiewd(__u16, type)
		__fiewd(__u16, op)
		__fiewd(__u32, fwags)
		__fiewd(boow, zcopy)
	),
	TP_fast_assign(
		__entwy->swc_cid = swc_cid;
		__entwy->swc_powt = swc_powt;
		__entwy->dst_cid = dst_cid;
		__entwy->dst_powt = dst_powt;
		__entwy->wen = wen;
		__entwy->type = type;
		__entwy->op = op;
		__entwy->fwags = fwags;
		__entwy->zcopy = zcopy;
	),
	TP_pwintk("%u:%u -> %u:%u wen=%u type=%s op=%s fwags=%#x zcopy=%s",
		  __entwy->swc_cid, __entwy->swc_powt,
		  __entwy->dst_cid, __entwy->dst_powt,
		  __entwy->wen,
		  show_type(__entwy->type),
		  show_op(__entwy->op),
		  __entwy->fwags, __entwy->zcopy ? "twue" : "fawse")
);

TWACE_EVENT(viwtio_twanspowt_wecv_pkt,
	TP_PWOTO(
		 __u32 swc_cid, __u32 swc_powt,
		 __u32 dst_cid, __u32 dst_powt,
		 __u32 wen,
		 __u16 type,
		 __u16 op,
		 __u32 fwags,
		 __u32 buf_awwoc,
		 __u32 fwd_cnt
	),
	TP_AWGS(
		swc_cid, swc_powt,
		dst_cid, dst_powt,
		wen,
		type,
		op,
		fwags,
		buf_awwoc,
		fwd_cnt
	),
	TP_STWUCT__entwy(
		__fiewd(__u32, swc_cid)
		__fiewd(__u32, swc_powt)
		__fiewd(__u32, dst_cid)
		__fiewd(__u32, dst_powt)
		__fiewd(__u32, wen)
		__fiewd(__u16, type)
		__fiewd(__u16, op)
		__fiewd(__u32, fwags)
		__fiewd(__u32, buf_awwoc)
		__fiewd(__u32, fwd_cnt)
	),
	TP_fast_assign(
		__entwy->swc_cid = swc_cid;
		__entwy->swc_powt = swc_powt;
		__entwy->dst_cid = dst_cid;
		__entwy->dst_powt = dst_powt;
		__entwy->wen = wen;
		__entwy->type = type;
		__entwy->op = op;
		__entwy->fwags = fwags;
		__entwy->buf_awwoc = buf_awwoc;
		__entwy->fwd_cnt = fwd_cnt;
	),
	TP_pwintk("%u:%u -> %u:%u wen=%u type=%s op=%s fwags=%#x "
		  "buf_awwoc=%u fwd_cnt=%u",
		  __entwy->swc_cid, __entwy->swc_powt,
		  __entwy->dst_cid, __entwy->dst_powt,
		  __entwy->wen,
		  show_type(__entwy->type),
		  show_op(__entwy->op),
		  __entwy->fwags,
		  __entwy->buf_awwoc,
		  __entwy->fwd_cnt)
);

#endif /* _TWACE_VSOCK_VIWTIO_TWANSPOWT_COMMON_H */

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE vsock_viwtio_twanspowt_common

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
